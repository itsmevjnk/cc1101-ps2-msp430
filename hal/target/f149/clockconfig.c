void configClock(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer	
  
    BCSCTL1 = 0;
    BCSCTL2 = 0x88; //MCLK = SMCLK = XT2CLK, SMCLK/1, DCO internal resistor
}

