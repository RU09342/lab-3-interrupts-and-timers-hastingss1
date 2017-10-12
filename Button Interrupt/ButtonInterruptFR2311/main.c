#include <msp430.h> 


/**
 * main.c
 */

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
         P1OUT ^= BIT0;
         P1IFG &= ~BIT1;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1DIR |= 0x01;

    P1IE |= BIT1;
    P1IES |= BIT1;
    P1OUT &= ~BIT0;

__bis_SR_register(LPM4_bits + GIE);
}
