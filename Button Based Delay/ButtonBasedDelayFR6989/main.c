#include <msp430.h>
 int flag = 0; //flag to indicate when user changed led blink speed
    int start = 0; //time button is pressed
    int end = 0; //time button is depressed
    int counter = 200; //initial blink speed of 10 hz
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;

    P1REN |= BIT1; //setup button 1.1 using pull up resistor and enable
    P1OUT |= BIT1;
    P1DIR |= BIT1;
    P1IE |= BIT1;
    P1IES |= BIT1;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Timer0_A0 setup
    TA0CCTL0 = CCIE;                              // TACCR0 interrupt enabled
    TA0CCR0 = 200; //set initial blink led speed of 10 hz
    TA0CTL = TASSEL_1 | MC_1 + ID_3;                     // ACLK, up mode

    __bis_SR_register(GIE);           // Enter LPM3 w/ interrupt

    while(1) {
        if(flag) { //checks if user has depressed the button
            flag = 0; //reset flag
            if(end >start) { //check that timer didn't reset after passing 65535
                counter = end - start; //calculate new blink speed
                TA0CCR0 = counter + TA0R; //assign new speed
            }
            else {
                counter = 65535 - start + end; //calculate new blink speed when timer passed 65535 while button was pressed
                TA0CCR0 = counter + TA0R; //assign new speed
            }
        }
    }
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) {

    TA0CCR0 += counter; //increment timer A0
    P1OUT ^= BIT0; //toggle led0

}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {

    if(P1IES & BIT1) { //check that button is pressed
        start = TA0R; //assign time that button was pressed
    }
    else {
        end = TA0R; //assign time that button was depressed
        flag = 1; //throw flag to indicate a change in blink speed
    }
         P1IES ^= BIT1; //reset enable
         P1IFG &= ~BIT1; //reset flag
}
