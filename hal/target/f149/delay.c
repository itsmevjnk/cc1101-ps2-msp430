
#include <msp430.h>

void initTimer_A(void);
void delayMS(int msecs);

unsigned int OFCount;

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
	P1DIR |= BIT0; //Configure P1.0 as Output

	//Set MCLK = SMCLK = 1MHz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	initTimer_A();
	_enable_interrupt();

	while(1)
	{
		P1OUT |= BIT0; //Drive P1.0 HIGH - LED1 ON
		delayMS(500); //Wait 0.5 Secs

		P1OUT &= ~BIT0; //Drive P1.0 LOW - LED1 OFF
		delayMS(500); //Wait 0.5 Secs
	}
}

void initTimer_A(void)
{
	//Timer0_A3 Configuration
	TACCR0 = 0; //Initially, Stop the Timer
	TACCTL0 |= CCIE; //Enable interrupt for CCR0.
	TACTL = TASSEL_2 + ID_0 + MC_1; //Select SMCLK, SMCLK/1, Up Mode
}

void delayMS(int msecs)
{
	OFCount = 0; //Reset Over-Flow counter
	TACCR0 = 1000-1; //Start Timer, Compare value for Up Mode to get 1ms delay per loop
	//Total count = TACCR0 + 1. Hence we need to subtract 1.

	while(i<=msecs);

	TACCR0 = 0; //Stop Timer
}

//Timer ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void)
{
	OFCount++; //Increment Over-Flow Counter
}