#include <msp430.h>
 int flag = 0;  //flag to indicate user has changed blink speed
    int start = 0; //time button is pressed
    int end = 0; //time button is depressed
    int counter = 200; //initial timer speed
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;

    P5REN |= BIT6;                                 //button 5.6 setup using pull-up resistor and enable
    P5OUT |= BIT6;
    P5DIR |= BIT6;
    P5IE |= BIT6;
    P5IES |= BIT6;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Timer0_A0 setup
    TA0CCTL0 = CCIE;                              // TACCR0 interrupt enabled
    TA0CCR0 = 200;                                  //blink at 10hz
    TA0CTL = TASSEL_1 | MC_1 + ID_3;                     // ACLK, up mode

    __bis_SR_register(GIE);           // Enter LPM3 w/ interrupt

    while(1) {
        if(flag) { //checks if user changed blink speed
            flag = 0; //reset flag
            if(end >start) { //check to see that timer didn't reset after passing 65535
                counter = end - start; //calculate new blink speed
                TA0CCR0 = counter + TB0R; //assign new blink speed
            }
            else {
                counter = 65535 - start + end; //calculate new blink speed if timer passed 65535
                TA0CCR0 = counter + TB0R;  //assign new blink speed
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
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void) { //button 5.6 interrupt service routine

    if(P5IES & BIT6) {  //if button is pressed
        start = TA0R; //assign time button was pressed
    }
    else {
        end = TA0R; //assign time button was depressed
        flag = 1; //throw flag to indicate change in blink speed
    }
         P5IES ^= BIT6; //reset enable
         P5IFG &= ~BIT6; //reset flag
}
