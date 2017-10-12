#include <msp430.h>
 int flag = 0; //flag to indicate button was depressed and a change in blink led speed
    int start = 0; //time button was pressed
    int end = 0; //time button was depressed
    int counter = 100; //initial blink led speed of 10 hz
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin1 as output
    P1OUT |= BIT0;

    P1REN |= BIT3;                              //setup button 1.3 using pull up resistor and enable
    P1OUT |= BIT3;
    P1IE |= BIT3;
    P1IES |= BIT3;
    P1IFG &= ~BIT3;

    // Timer1_B3 setup
    CCTL0 |= CCIE;                              //enable interrupt
    CCTL0 &= ~TAIFG;                            //clear flag
    TA0CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TA0CCR0 = 100; //set blink led speed of 10 hz
    TA0CTL = TASSEL_1 + MC_2 + ID_3;                     // ACLK, up mode

    __bis_SR_register(GIE);           // Enter LPM3 w/ interrupt

    while(1) {
        if(flag) { //check if button was depressed indicating a new blink led speed
            flag = 0; //reset flag
            if(end >start) { //check that timer didn't pass 65535 while button was pressed
                counter = end - start; //calculate new blink led speed
                TA0CCR0 = counter + TA0R; //assign new blink led speed
            }
            else { //timer passed 65535 while button was pressed
                counter = 65535 - start + end; //calculate new blink led speed
                TA0CCR0 = counter + TA0R; //assign new blink led speed
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
__interrupt void Port_1(void) { //button 1.3 interrupt service routine

    if(P1IES & BIT3) { //if button 1.3 is pressed
        start = TA0R; //assign start time
    }
    else { //button 1.3 is depressed
        end = TA0R; //assign end time
        flag = 1; //set flag to indicate a change in blink led speed
    }
         P1IES ^= BIT3; //reset enable
         P1IFG &= ~BIT3; //reset flag
}
