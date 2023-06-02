#include "ps2.h"
#include "hal_gpio.h"
#include "hal_spi.h"
#include "hal_timer.h"
#include "delay.h"

static unsigned char ps2_last_read = 0; // timestamp of last time the controller was read

#define PS2_ATT_LOW                 {while(hal_timer_ticks - ps2_last_read < PS2_DELAY_PACKET); hal_gpio_out_low(PS2_PORT_ATT, PS2_PIN_ATT); delay_us(PS2_DELAY_BYTE);} // activate ATT pin
#define PS2_ATT_HIGH                {hal_gpio_out_high(PS2_PORT_ATT, PS2_PIN_ATT);} // deactivate ATT pin

unsigned char ps2_buffer[32];

unsigned char ps2_transfer(unsigned char command) {
  PS2_ATT_LOW;
  
  unsigned char ret = 0; // return value
  if(hal_spi_transfer(0x01) != 0xFF) goto finish; // first byte mismatch
  ret = hal_spi_transfer(command);
  if(hal_spi_transfer(0x00) != 0x5A) { ret = 0; goto finish; } // third byte mismatch
  
  for(unsigned char i = 0; i < (ps2_transfer_words(ret) << 1); i++) ps2_buffer[i] = hal_spi_transfer(ps2_buffer[i]); // this first reads ps2_buffer[i] to get the command byte, then saves the received data byte to ps2_buffer[i]
  
finish:
  PS2_ATT_HIGH;
  return ret;
}

void ps2_init(void) {
  /* configure the GPIO pin for ATT */
  hal_gpio_func_io(PS2_PORT_ATT, PS2_PIN_ATT);
  hal_gpio_dir_output(PS2_PORT_ATT, PS2_PIN_ATT);
  hal_gpio_out_high(PS2_PORT_ATT, PS2_PIN_ATT);
  
  
}
