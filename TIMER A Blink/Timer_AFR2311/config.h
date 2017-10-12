/*
 * config.h
 *
 *  Created on: Oct 4, 2017
 *      Author: Sean
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#define MSP430FR2311
//#define MSP430G2553
//#define MSP430FR5994
//#define MSP430F5529
//#define MSP430FR6989


#ifndef MSP430FR2311
#define MSP430FR2311

void LED0Setup() {
    #ifndef MSP430FR2311
    P1DIR |= BIT0;                                // Set Pin as output
    #endif
}

void LED1Setup() {
    #ifndef MSP430FR2311
    P2DIR |= BIT0;                                // Set Pin as output
    #endif
}
void SetLED0(int on) {
    #ifndef MSP430FR2311
        if(on) {
           P1OUT |= BIT0;                                /Turn on LED
        }
        else {
            P1OUT &= ~BIT0; //Turn off LED
        }
    #endif
}

void SetLED1(int on) {
    #ifndef MSP430FR2311
        if(on) {
           P2OUT |= BIT0;                                /Turn on LED
        }
        else {
           P2OUT &= ~BIT0; //Turn off LED
        }
    #endif
}

#define

void ButtonSetup() {
    #ifndef MSP430FR2311
        P1REN |= BIT1;
        P1OUT |= BIT1;
        P1DIR &= ~BIT1;
    #endif
}

#define P2DIR |= BIT0;                                // Set Pin as output
#define P2OUT |= BIT0;

#endif /* MSP430FR2311 */







#ifndef MSP430G2553
#define MSP430G2553

#define CTS_IN P1IN
#define CTS_PIN BIT6

#define nSEL_PIN BIT2
#define nSEL_OUT P3OUT

#define nIRQ_DIR P3DIR
#define nIRQ_PIN BIT6

#define GPIO1_PIN BIT5
#define GPIO1_DIR P3DIR
#define GPIO1_IN  P3IN

#endif /* MSP430G2553 */






#ifndef MSP430FR5994
#define MSP430FR5994

#define CTS_IN P1IN
#define CTS_PIN BIT6

#define nSEL_PIN BIT2
#define nSEL_OUT P3OUT

#define nIRQ_DIR P3DIR
#define nIRQ_PIN BIT6

#define GPIO1_PIN BIT5
#define GPIO1_DIR P3DIR
#define GPIO1_IN  P3IN

#endif /* MSP430FR5994 */







#ifndef MSP430F5529
#define MSP430F5529

#define CTS_IN P1IN
#define CTS_PIN BIT6

#define nSEL_PIN BIT2
#define nSEL_OUT P3OUT

#define nIRQ_DIR P3DIR
#define nIRQ_PIN BIT6

#define GPIO1_PIN BIT5
#define GPIO1_DIR P3DIR
#define GPIO1_IN  P3IN

#endif /* MSP430F5529 */






#ifndef MSP430FR6989
#define MSP430FR6989

#define CTS_IN P1IN
#define CTS_PIN BIT6

#define nSEL_PIN BIT2
#define nSEL_OUT P3OUT

#define nIRQ_DIR P3DIR
#define nIRQ_PIN BIT6

#define GPIO1_PIN BIT5
#define GPIO1_DIR P3DIR
#define GPIO1_IN  P3IN

#endif /* MSP430FR6989 */



#endif /* CONFIG_H_ */
