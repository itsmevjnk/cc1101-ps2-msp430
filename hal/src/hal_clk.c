#include "hal_clk.h"
#include "hal_hwdef.h"

#if defined HAL_CLK_BASIC

void hal_clk_init(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  
  BCSCTL1 = 0; // enable XT2
  
  /* wait until crystal is ready to go (no OSCFault) */
  do {
    IFG1 &= ~OFIFG;
    for(unsigned char i = 0xFF; i > 0; i--);
  } while(IFG1 & OFIFG);
  
  BCSCTL2 = 0x88; // MCLK = SMCLK = XT2CLK, SMCLK/1, DCO internal resistor
}

#else
#error "No system clock module type defined"
#endif