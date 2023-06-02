#include "hal_hwdef.h"

#include "hal_spi.h"
#include "hal_gpio.h"

/* low level functions */
#if defined HAL_SPI_INTERFACE_USART0 || defined HAL_SPI_INTERFACE_USART1
void hal_spi_init(void) {
  HAL_SPI_REG_UxCTL = SWRST; // put USART peripheral in reset state
  
  /* general USART configuration */
  HAL_SPI_REG_UxCTL |= CHAR + SYNC + MM; // USART master, SPI mode, 8-bit data length
  HAL_SPI_REG_UxTCTL |= CKPH + CKPL + SSEL1 + SSEL0 + STC; // 3-pin SPI mode, using SMCLK as clock source, SPI mode 2
  
  /* baud rate setting: UxBR = BRCLK / baud */
  HAL_SPI_REG_UxBR0 = (HAL_CLK_SMCLK / HAL_SPI_CLKSPEED) & 0xFF;
  HAL_SPI_REG_UxBR1 = (HAL_CLK_SMCLK / HAL_SPI_CLKSPEED) >> 8;
  
  HAL_SPI_REG_MEx |= HAL_SPI_BIT_USPIEx; // enable SPI peripheral
  
  /* set up pins */
  hal_gpio_func_peripheral(HAL_SPI_PORT_SIMO, HAL_SPI_PIN_SIMO);
  hal_gpio_func_peripheral(HAL_SPI_PORT_SOMI, HAL_SPI_PIN_SOMI);
  hal_gpio_func_peripheral(HAL_SPI_PORT_UCLK, HAL_SPI_PIN_UCLK);
  
  HAL_SPI_REG_UxCTL &= ~SWRST; // disable reset state, essentially turning on the peripheral
}

/* "building blocks" for interface functions */
#define HAL_SPI_WAIT_RXBUF              {while(!(HAL_SPI_REG_IFGx & HAL_SPI_BIT_URXIFGx));} // wait until there is a byte to receive
#define HAL_SPI_WAIT_TXBUF              {while(!(HAL_SPI_REG_IFGx & HAL_SPI_BIT_UTXIFGx));} // wait until the transmit buffer is ready to receive bytes
#define HAL_SPI_GET_RXBUF               HAL_SPI_REG_UxRXBUF // get a byte from receive buffer
#define HAL_SPI_SET_TXBUF(x)            {HAL_SPI_REG_UxTXBUF = (x);} // send a byte to transmit buffer and stage for transmission

#else
#error "No SPI interface defined"
#endif

/* high level interface functions */
unsigned char hal_spi_transfer(unsigned char txbyte) {
  HAL_SPI_WAIT_TXBUF;
  HAL_SPI_SET_TXBUF(((txbyte & 1) << 7) | ((txbyte & 2) << 5) | ((txbyte & 4) << 3) | ((txbyte & 8) << 1) | ((txbyte & 16) >> 1) | ((txbyte & 32) >> 3) | ((txbyte & 64) >> 5) | ((txbyte & 128) >> 7)); // bit order swapping
  HAL_SPI_WAIT_RXBUF; // there's no need to wait for transmission to finish as SPI is a duplex protocol, as soon as transmission is finish reception will finish too
  unsigned char rxbyte = HAL_SPI_GET_RXBUF;
  return (((rxbyte & 1) << 7) | ((rxbyte & 2) << 5) | ((rxbyte & 4) << 3) | ((rxbyte & 8) << 1) | ((rxbyte & 16) >> 1) | ((rxbyte & 32) >> 3) | ((rxbyte & 64) >> 5) | ((rxbyte & 128) >> 7));
}
