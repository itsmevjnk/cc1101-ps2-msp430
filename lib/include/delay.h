#ifndef DELAY_H
#define DELAY_H

#include "hal_hwdef.h"

void delay_ms(unsigned int t); // timer-based delay - make sure you have initialized the timer (in hal_timer)!
void delay_us(unsigned int t);

/* NOP delay macros - adapted from https://github.com/ab2tech/msp430/blob/master/include/msp/delay.h */
#define delay_us_nop(__us) \
  if((unsigned long) ((HAL_CLK_MCLK / 1000000UL) * __us) != (HAL_CLK_MCLK / 1000000UL) * __us)\
        __delay_cycles((unsigned long) ( (HAL_CLK_MCLK / 1000000UL) * __us)+1);\
  else __delay_cycles((unsigned long) ( (HAL_CLK_MCLK / 1000000UL) * __us))

// #define delay_us                        delay_us_nop // there's no other alternatives as of now

#define delay_ms_nop(__ms) \
  if((unsigned long) ((HAL_CLK_MCLK / 1000UL) * __ms) != (HAL_CLK_MCLK / 1000UL) * __ms)\
        __delay_cycles((unsigned long) ( (HAL_CLK_MCLK / 1000UL) * __ms)+1);\
  else __delay_cycles((unsigned long) ( (HAL_CLK_MCLK / 1000UL) * __ms))

#endif