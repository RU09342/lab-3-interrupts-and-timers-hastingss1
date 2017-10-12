#include <msp430.h> 


/**
 * main.c
 */

#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void) {
    if(P5IN & ~BIT6) {
         P1OUT ^= BIT0;
         P5IFG &= ~BIT6;
    }
    if(P5IN & ~BIT5) {
        P1OUT ^= BIT1;
        P5IFG &= ~BIT5;
    }

}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;
    P5REN |= BIT6;
    P5OUT |= BIT6;
    P5DIR |= BIT6;

    P5IE |= BIT6;
    P5IES |= BIT6;

    P5REN |= BIT5;
        P5OUT |= BIT5;
        P5DIR |= BIT5;

        P5IE |= BIT5;
        P5IES |= BIT5;



    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P1DIR |= BIT1;
    P1OUT &= ~BIT1;
__bis_SR_register(LPM4_bits + GIE);
}
