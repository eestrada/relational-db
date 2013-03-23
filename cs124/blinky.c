//******************************************************************************
//  CS/ECEn 124 Lab 1 - blinky.c: Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//
//            MSP430F2013/F2274
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->GREEN LED
//           |             P1.1|-->RED LED (F2274)
//
//******************************************************************************
#include "msp430x20x3.h"
//#include "msp430x22x4.h"

volatile unsigned int i;                    // volatile to prevent optimization

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  for (;;)
  {
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
    i = 0;                                  // Delay
    while (--i);
  }
}
