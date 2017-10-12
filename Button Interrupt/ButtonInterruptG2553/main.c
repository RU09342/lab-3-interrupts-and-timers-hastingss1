#include <msp430.h> 


/**
 * main.c
 */


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;                                // Set Pin1 as output
      P1OUT |= BIT0;

      P1REN |= BIT3; //setup button 1.3
      P1OUT |= BIT3;
      P1IE |= BIT3;
      P1IES |= BIT3;
      P1IFG &= ~BIT3;

__bis_SR_register(LPM4_bits + GIE); //low power
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) { //button 1.3 interrupt service routine
         P1OUT ^= BIT0; //toggle led 1.0
         P1IFG &= ~BIT3; //reset flag
}
