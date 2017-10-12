#include <msp430.h> 
/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430FR231x Demo - Timer1_B3, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK
//
//  Description: Toggle P1.0 using software and TB1_0 ISR. Timer1_B is
//  configured for UP mode, thus the timer overflows when TBR counts
//  to CCR0.
//
//  ACLK = TBCLK = 32768Hz, MCLK = SMCLK  = default DCO = ~1MHz
//
//          MSP430FR2311
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   Darren Lu
//   Texas Instruments Inc.
//   Oct. 2015
//   Built with IAR Embedded Workbench v6.30 & Code Composer Studio v6.1
//******************************************************************************
#include <msp430.h>
 int flag = 0;
    int start = 0;
    int end = 0;
    int counter = 200;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Pin as output
    P1OUT |= BIT0;

    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1DIR |= BIT1;
    P1IE |= BIT1;
    P1IES |= BIT1;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Timer1_B3 setup
    TA0CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TA0CCR0 = 200;
    TA0CTL = TASSEL_1 | MC_1 + ID_3;                     // ACLK, up mode

    __bis_SR_register(GIE);           // Enter LPM3 w/ interrupt

    while(1) {
        if(flag) {
            flag = 0;
            if(end >start) {
                counter = end - start;
                TA0CCR0 = counter + TA0R;
            }
            else {
                counter = 65535 - start + end;
                TA0CCR0 = counter + TA0R;
            }
        }
    }
}

// Timer B1 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) {

    TA0CCR0 += counter;
    P1OUT ^= BIT0;

}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {

    if(P1IES & BIT1) {
        start = TA0R;
    }
    else {
        end = TA0R;
        flag = 1;
    }
         P1IES ^= BIT1;
         P1IFG &= ~BIT1;
}
