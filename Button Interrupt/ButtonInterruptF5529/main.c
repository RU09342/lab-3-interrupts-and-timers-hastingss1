#include <msp430.h> 


/**
 * main.c
 */

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) { //button 1.1 interrupt service routine
         P1OUT ^= BIT0; //toggle led0
         P1IFG &= ~BIT1; //reset interrupt flag
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1REN |= BIT1; //setup button 1.1
    P1OUT |= BIT1;
    P1DIR |= BIT1;
    P1DIR |= BIT0; //setup led0

    P1IE |= BIT1; //setup button 1.1 interrupt
    P1IES |= BIT1;
    P1OUT &= ~BIT0; //turn off led 1.0

__bis_SR_register(LPM4_bits + GIE); //low power
}
