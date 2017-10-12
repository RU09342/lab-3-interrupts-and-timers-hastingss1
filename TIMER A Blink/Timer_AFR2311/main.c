
#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;

    P2DIR |= BIT0;                                // Set Pin as output
    P2OUT |= BIT0;
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Timer1_B3 setup
    TB1CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TB0CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TB1CCR0 = 50000;
    TB0CCR0 = 25000;
    TB1CTL = TBSSEL_1 | MC_1;                     // ACLK, up mode
    TB0CTL = TBSSEL_1 | MC_1;                     // ACLK, up mode

    __bis_SR_register(LPM3_bits | GIE);           // Enter LPM3 w/ interrupt
}

// Timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    P1OUT ^= BIT0; //toggle led 1.0
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{
    P2OUT ^= BIT0; //toggle led 2.0
}
