#include <msp430.h> 


/**
 * main.c
 */

#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void) { //button 5.5 and 5.6 interrupt service routine
    if(P5IN & ~BIT6) { //if button 5.6 is pressed
         P1OUT ^= BIT0; //toggle led 1.0
         P5IFG &= ~BIT6; //reset flag
    }
    if(P5IN & ~BIT5) { //if button 5.5 is pressed
        P1OUT ^= BIT1; //toggle led 1.1
        P5IFG &= ~BIT5; //reset flag
    }

}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5; //disable high impedance mode
    P5REN |= BIT6; //setup button 5.6
    P5OUT |= BIT6;
    P5DIR |= BIT6;

    P5IE |= BIT6; //setup button 5.6 interrupt
    P5IES |= BIT6;

    P5REN |= BIT5; //setup button 5.5
        P5OUT |= BIT5;
        P5DIR |= BIT5;

        P5IE |= BIT5; //setup button 5.5 interrupt
        P5IES |= BIT5;

    P1DIR |= BIT0; //setup led 1.0
    P1OUT &= ~BIT0;
    P1DIR |= BIT1; //setup led 1.1
    P1OUT &= ~BIT1;
__bis_SR_register(LPM4_bits + GIE); //low power
}
