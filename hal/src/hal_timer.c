#include "hal_timer.h"
#include "hal_hwdef.h"

volatile unsigned long hal_timer_ticks = 0;

void hal_timer_init(void) {
  /* initialize tick timer */
  HAL_TIMER_REG_TAxCCR0 = 0; // stop the timer
  HAL_TIMER_REG_TAxCCTL0 |= CCIE; // enable compare/capture interrupt
  HAL_TIMER_REG_TAxCTL = TASSEL_2 + ID_0 + MC_1; // select SMCLK, prescaler = 1, up mode
  HAL_TIMER_REG_TAxCCR0 = (HAL_CLK_SMCLK / 1000) - 1; // set compare value so that the interrupt is triggered every 1ms
  
  /* initialize microsecond delay timer */
  HAL_TIMER_REG_TBxCTL = TBSSEL_2 + TBCLR; // select SMCLK, prescaler = 1, clear TBR (mode will be set when we use it)
  
  __bis_SR_register(GIE); // enable interrupts
}

/* Timer_A capture/compare ISR */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void hal_timer_ccr0_isr(void) {
  hal_timer_ticks++;
}