///******************************************************************************
//  Lab 8a - Etch-a-Sketch
//
//  Description:
//
//	"Write a C language program that uses the sampled values from two
//	potentiometers to draw (etch) lines on the LCD. Use a low-pass filter
//	to smooth out the sampled values. Program one push button to clear
//	the LCD and another to toggle the size of the drawing pen. Display
//	the pen coordinates in the lower right corner of the display."
//
//   Author:	Paul Roper, Brigham Young University
//				March 2010
//
//   Built with Code Composer Essentials Version: 3.2
//*******************************************************************************
//
//	                  MSP430F2274 (REV C)
//	               .----------------------.          LEFT         RIGHT
//	     RED LED-->|P1.0    (ACLK/A0) P2.0|<--SW_1
//	   GREEN LED-->|P1.1   (SMCLK/A1) P2.1|<--(H)    SW_2         EZ0_TX
//	eZ430 BUTTON-->|P1.2     (TA0/A2) P2.2|<--(D)    ADXL_INT     SW_3
//	           N.C.|P1.3     (TA1/A3) P2.3|<--(E)    SW_4         SERVO_3
//	           N.C.|P1.4     (TA2/A4) P2.4|-->(F)    LCD_BLT      SERVO_4
//	           N.C.|P1.5              P2.5| N.C.
//	           N.C.|P1.6          XIN P2.6|-->LED_1
//	           N.C.|P1.7         XOUT P2.7|-->LED_2
//                 |     (UCB0STE/A5) P3.0|-->i2c_RST
//                 |        (UCB0SDA) P3.1|<->i2c_SDA
//                 |        (UCB0SCL) P3.2|-->i2c_SCL
//                 |        (UCB0CLK) P3.3|-->LED_3/EZ0_RX
//	               |                  P3.4| N.C.
//	               |                  P3.5| N.C.
//	               |                  P3.6| N.C.
//	               |                  P3.7| N.C.
//	               |                  P4.0| N.C.
//	               |                  P4.1| N.C.
//	               |                  P4.2| N.C.
//	               |        (TB0/A12) P4.3|-->(G)    RPOT         EZ0_AN
//	               |        (TB1/A13) P4.4|-->(A)    LPOT         SERVO_1
//	               |        (TB2/A14) P4.5|-->(B)    TRANSDUCER   SERVO_2
//	               |     (TBOUTH/A15) P4.6|-->(C)    THERMISTOR   LED_4
//	               |                  P4.7| N.C.
//	               '----------------------'
//
//******************************************************************************
//
#include "msp430x22x4.h"
#include "eZ430X.h"
#include "lcd.h"
#include "adc.h"
#include "graphics.h"
#include "etch-a-sketch.h"

//------------------------------------------------------------------------------
// INITIALIZE SYSTEM CONSTANTS
//
#define myCLOCK	1200000					// clock speed
#define WDT_CLK	32000					// 32 Khz WD clock (@1 Mhz)
#define	WDT_CTL	WDT_MDLY_32				// WDT SMCLK, ~32ms
#define	WDT_CPS	myCLOCK/WDT_CLK			// WD clocks / second count

//------------------------------------------------------------------------------
// Watchdog interrupt variables
volatile int WDT_cps_cnt;
volatile int WDT_delay;

extern const unsigned char byu_image[];	// BYU logo

#define POT_THRESHOLD	3

//------------------------------------------------------------------------------
//
void main(void)
{
	int oldLPot, oldRPot;

	// initialize eZ430X development board
	eZ430X_init(CALDCO_1MHZ);			// init board

	// configure Watchdog
	WDT_cps_cnt = WDT_CPS;				// set WD 1 second counter
	WDT_delay = 0;						// no delay
	WDTCTL = WDT_CTL;					// Set Watchdog interval to ~32ms
	IE1 |= WDTIE;						// Enable WDT interrupt

	// configure other peripherals
	ADC_init();							// init ADC
	lcd_init();							// init LCD
	lcd_FRAM_init();					// clear lcd FRAM memory

	__bis_SR_register(GIE);				// enable interrupts

	lcd_image(byu_image, 40, 11);		// display BYU
	lcd_backlight(ON);					// turn on LCD
	lcd_display(LCD_2X_FONT|LCD_PROPORTIONAL);
	lcd_cursor(4, 2);					// set display coordinates
	lcd_printf("Etch-a-Sketch");
	lcd_display(~(LCD_2X_FONT|LCD_PROPORTIONAL));

	oldRPot = ADC_read(12);				// make initial read of pots
	oldLPot = ADC_read(13);

	while (1)
	{
		int R_pot, L_pot;

		R_pot = ADC_read(12);			// read potentiometrs
		L_pot = ADC_read(13);

		// check to see if movement exceeds threshold
		if ((abs(R_pot - oldRPot) > POT_THRESHOLD) ||
			(abs(L_pot - oldLPot) > POT_THRESHOLD))
		{
			oldRPot = R_pot;			// update old values
			oldLPot = L_pot;

			lcd_circle(R_pot>>2, 47, 20);

			lcd_cursor(60, 0);			// output coordinates
			lcd_printf("%d,%d   ", L_pot, R_pot);
		}
	}
} // end main


//------------------------------------------------------------------------------
//	Watchdog Timer ISR
//
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	if (--WDT_cps_cnt == 0)				// 1 second?
	{
		LED_GREEN_TOGGLE;				// toggle green LED
		WDT_cps_cnt = WDT_CPS;			// reset counter
	}

	if (WDT_delay)						// process any delays
	{
		WDT_delay--;					// decrement delay counter
	}
} // end WDT_ISR
