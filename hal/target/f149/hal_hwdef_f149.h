#ifndef HAL_HWDEF_F149_H
#define HAL_HWDEF_F149_H

#if defined HAL_HW_F149

#include "io430.h"

/* SPI interface: USART0/1 supported (F149) */
//#define HAL_SPI_INTERFACE_USART0
#define HAL_SPI_INTERFACE_USART1

/* SPI clock speed (Hz) */
#define HAL_SPI_CLKSPEED                        250000UL
/* system clock frequencies (Hz) */
#define HAL_CLK_MCLK                            8000000UL
#define HAL_CLK_SMCLK                           8000000UL

/* system clock module */
#define HAL_CLK_BASIC

/* Timer_A (system tick counter) register configuration */
#define HAL_TIMER_REG_TAxCTL                    TACTL
#define HAL_TIMER_REG_TAxCCTL0                  TACCTL0
#define HAL_TIMER_REG_TAxCCR0                   TACCR0

/* Timer_B (microsecond delay timer) register configuration */
#define HAL_TIMER_REG_TBxCTL                    TBCTL
#define HAL_TIMER_REG_TBxCCTL0                  TBCCTL0
#define HAL_TIMER_REG_TBxCCR0                   TBCCR0

//------------------------------------------------------------------------------
// SPI hardware configuration 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#if defined HAL_SPI_INTERFACE_USART0

// register definitions
#define HAL_SPI_REG_UxCTL                       U0CTL
#define HAL_SPI_REG_UxTCTL                      U0TCTL
#define HAL_SPI_REG_UxBR0                       U0BR0
#define HAL_SPI_REG_UxBR1                       U0BR1
#define HAL_SPI_REG_UxMCTL                      U0MCTL
#define HAL_SPI_REG_MEx                         ME1
#define HAL_SPI_REG_IFGx                        IFG1
#define HAL_SPI_REG_UxRXBUF                     U0RXBUF
#define HAL_SPI_REG_UxTXBUF                     U0TXBUF


// register bit definitions
#define HAL_SPI_BIT_USPIEx                      USPIE0
#define HAL_SPI_BIT_URXIFGx                     URXIFG0
#define HAL_SPI_BIT_UTXIFGx                     UTXIFG0


// pin definitions
#define HAL_SPI_PORT_SIMO                       3
#define HAL_SPI_PIN_SIMO                        1

#define HAL_SPI_PORT_SOMI                       3
#define HAL_SPI_PIN_SOMI                        2

#define HAL_SPI_PORT_UCLK                       3
#define HAL_SPI_PIN_UCLK                        3

//------------------------------------------------------------------------------

#elif defined HAL_SPI_INTERFACE_USART1

// register definitions
#define HAL_SPI_REG_UxCTL                       U1CTL
#define HAL_SPI_REG_UxTCTL                      U1TCTL
#define HAL_SPI_REG_UxBR0                       U1BR0
#define HAL_SPI_REG_UxBR1                       U1BR1
#define HAL_SPI_REG_UxMCTL                      U1MCTL
#define HAL_SPI_REG_MEx                         ME2
#define HAL_SPI_REG_IFGx                        IFG2
#define HAL_SPI_REG_UxRXBUF                     U1RXBUF
#define HAL_SPI_REG_UxTXBUF                     U1TXBUF


// register bit definitions
#define HAL_SPI_BIT_USPIEx                      USPIE1
#define HAL_SPI_BIT_URXIFGx                     URXIFG1
#define HAL_SPI_BIT_UTXIFGx                     UTXIFG1


// pin definitions
#define HAL_SPI_PORT_SIMO                       5
#define HAL_SPI_PIN_SIMO                        1

#define HAL_SPI_PORT_SOMI                       5
#define HAL_SPI_PIN_SOMI                        2

#define HAL_SPI_PORT_UCLK                       5
#define HAL_SPI_PIN_UCLK                        3

//------------------------------------------------------------------------------

#else
#error "No interface defined for SPI"
#endif

#endif

#endif