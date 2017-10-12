#include <msp430.h> 

 int flag = 0;                                    //flag to trip when button is fired to change led speed
    int start = 0;                                //time when user presses button
    int end = 0;                                  //time when user depresses button
    int counter = 200;                            //initial speed
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;

    P1REN |= BIT1;                                //Button1 setup using interrupt enable and pull up resistor to pin 1
    P1OUT |= BIT1;
    P1DIR |= BIT1;
    P1IE |= BIT1;
    P1IES |= BIT1;

    // Timer1_B3 setup
    TA0CCTL0 = CCIE;                              // TACCR0 interrupt enabled
    TA0CCR0 = 200;                                // TACCR0 timer set
    TA0CTL = TASSEL_1 | MC_1 + ID_3;              // ACLK, up mode

    __bis_SR_register(GIE);                       // Enter LPM3 w/ interrupt

    while(1) {
        if(flag) {                                //checks if user pressed button
            flag = 0;                             //reset flag
            if(end >start) {                      //check that timer didn't reset after reaching 65535
                counter = end - start;            //assign new led speed
                TA0CCR0 = counter + TA0R;         //update timer speed
            }
            else {
                counter = 65535 - start + end;    //accounts for clock resetting after reaching 65535
                TA0CCR0 = counter + TA0R;         //update timer speed
            }
        }
    }
}


#pragma vector = TIMER0_A0_VECTOR                 // Timer A0 interrupt service routine
__interrupt void Timer0_A0_ISR(void) {

    TA0CCR0 += counter;                           //Increment timer A0 with the new speed
    P1OUT ^= BIT0;                                //Toggle LED0

}
#pragma vector=PORT1_VECTOR                       //Button 1.1 interrupt service routine
__interrupt void Port_1(void) {

    if(P1IES & BIT1) {                            //check if button is pressed
        start = TA0R;                             //get start time
    }
    else {                                        //button is depressed
        end = TA0R;                               //get end time
        flag = 1;                                 //throw flag to indicate user set a new speed
    }
         P1IES ^= BIT1;                           //reset enable
         P1IFG &= ~BIT1;                          //reset flag
}
