
#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;

    P4DIR |= BIT7;                                // Set Pin as output
    P4OUT |= BIT7;

    // Timer1_B3 setup
    TA1CCTL0 = CCIE;                              // TACCR1 interrupt enabled
    TA0CCTL0 = CCIE;                              // TACCR0 interrupt enabled
    TA1CCR0 = 50000;                              //timer set
    TA0CCR0 = 25000;                              //timer set
    TA1CTL = TASSEL_1 | MC_1;                     // ACLK, up mode
    TA0CTL = TASSEL_1 | MC_1;                     // ACLK, up mode

    __bis_SR_register(LPM3_bits | GIE);           // Enter LPM3 w/ interrupt
}

// Timer B1 interrupt service routine
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
    P1OUT ^= BIT0; //toggle led 1.0
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)
{
    P4OUT ^= BIT7; //toggle led 4.7
}
