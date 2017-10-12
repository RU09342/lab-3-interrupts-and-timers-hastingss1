#include <msp430.h> 


/**
 * main.c
 */


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;                                // Set Pin as output
      P1OUT |= BIT0;

      P1REN |= BIT3;
      P1OUT |= BIT3;
      P1IE |= BIT3;
      P1IES |= BIT3;
      P1IFG &= ~BIT3;

__bis_SR_register(LPM4_bits + GIE);
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
         P1OUT ^= BIT0;
         P1IFG &= ~BIT3;
}
