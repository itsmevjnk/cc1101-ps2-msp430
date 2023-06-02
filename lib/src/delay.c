#include "delay.h"
#include "hal_timer.h"
#include "hal_hwdef.h"

void delay_ms(unsigned int t) {
  unsigned long t_start = hal_timer_ticks;
  while(hal_timer_ticks - t_start < t);
}

void delay_us(unsigned int t) {
  HAL_TIMER_REG_TBxCCR0 = (HAL_CLK_SMCLK / 1000000) * t;
  HAL_TIMER_REG_TBxCTL |= MC_0; // up mode
  while(!(HAL_TIMER_REG_TBxCTL & TBIFG)); // wait until TBR = TBCL0
  HAL_TIMER_REG_TBxCTL |= TBCLR; // reset, disabling Timer_B
}