//******************************************************************************
//******************************************************************************
//	eZ430X.c - eZ430X board system functions
//******************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//#include <math.h>

#include "msp430x22x4.h"
#include "eZ430X.h"

static void tdelay(unsigned int time);
static void LCD_WC(unsigned char cmd);
static void LCD_WD(unsigned char datum);
static void LCD_WC2(unsigned char cmd1, unsigned char cmd2);

//******************************************************************************
//	LCD Global variables (NOT ZERO'D!!!)
//
volatile unsigned char TXByteCnt;	// tx count
volatile unsigned char RXByteCnt;	// rx count
volatile unsigned char i2c_stop;	// enable stop

char lcd_X;							// x coordinate (0-159)
char lcd_Y;							// y coordinate (0-99)
char lcd_Page;						// page (0-12)
char lcd_Proportional;				// proportional character flag

unsigned char *TxData_ptr;			// Pointer to TX data
unsigned char TXData[8];
volatile unsigned char RxData;		// read data
char pBuffer[PRINT_BUFFER_SIZE+1];	// print buffer

//******************************************************************************
//	Initialization sequence for eZ430X MSP430F2274
//
void eZ430X_init(int clock)
{
	int i2c_fSCL;

	WDTCTL = WDTPW + WDTHOLD;				// Stop WDT

	// 	MSP430 Clock - Set DCO to 1-16 MHz:
	if (clock == CALDCO_16MHZ)
	{
		BCSCTL1 = CALBC1_16MHZ;				// Set range 16MHz
		DCOCTL = CALDCO_16MHZ;				// Set DCO step + modulation
		i2c_fSCL = 80;						// 16 MHz fSCL = SMCLK/12 = ~200kHz
	}
	else if (clock == CALDCO_12MHZ)
	{
		BCSCTL1 = CALBC1_12MHZ;				// Set range 12MHz
		DCOCTL = CALDCO_12MHZ;				// Set DCO step + modulation
		i2c_fSCL = 60;						// 12 MHz fSCL = SMCLK/60 = ~200kHz
	}
	else if (clock == CALDCO_8MHZ)
	{
		BCSCTL1 = CALBC1_8MHZ;				// Set range 8MHz
		DCOCTL = CALDCO_8MHZ;				// Set DCO step + modulation
//		i2c_fSCL = 40;						// 8.0 MHz fSCL = SMCLK/24 = ~200 kHz
		i2c_fSCL = 24;						// 8.0 MHz fSCL = SMCLK/24 = ~333 kHz
	}
	else
	{
		BCSCTL1 = CALBC1_1MHZ;				// Set range 1MHz
		DCOCTL = CALDCO_1MHZ;				// Set DCO step + modulation
		i2c_fSCL = 12;						// 1.2 MHz fSCL = SMCLK/12 = ~100kHz
	}

	// eZ430 red & green leds
	P1DIR |= 0x03;							// P1.0, P1.1 output
	P1OUT &= ~0x03;							// turn off

	// configure USCI_B0 for i2c operations
	//		P3.0/UCB0STE	output
	//      P3.1/UCB0SDA	input
	//	    P3.2/UCB0SCL	output
	//      P3.3/UCB0CLK	output
	P3DIR |= 0x0d;							// P3.0, P3,2, P3,3 outputs
	P3SEL |= 0x0e;                          // SCA, SCL, CLK USCI_B0 option select
	P3OUT &= ~0x01;							// ~CS (also reset LCD)
	// delay????
	wait(10);
	P3OUT |= 0x01;							// bring high
	P3SEL = 0x06;							// Assign I2C pins to USCI_B0

	// configure eZ430X LED's
	P2SEL &= ~0xc0;							// select GPIO (P2.6, P2.7)
	P2DIR |= 0xd0;							// backlight / LED_D / LED_C
	P2OUT &= ~0xd0;							// turn off

	P3DIR |= 0x08;							// LED_B
	P3OUT &= ~0x08;							// turn off

	P4DIR |= 0x40;							// LED_A
	P4OUT &= ~0x40;

	// configure buzzer (P4.5)
	P4DIR |= 0x20;							// Buzzer

	// eZ430X push buttons
	P2SEL &= ~0x0f;							// select GPIO
	P2DIR &= ~0x0f;							// Configure P2.0-3 as Inputs
	P2OUT |= 0x0f;							// use pull-ups
	P2IES |= 0x0f;							// high to low transition
	P2REN |= 0x0f;							// Enable pull-ups

	// USCI_B0 for i2c
	UCB0CTL1 |= UCSWRST;					// Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;	// I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;			// Use SMCLK, keep SW reset
	UCB0BR0 = i2c_fSCL;						// 1.2 MHz fSCL = SMCLK/12 = ~200kHz
	UCB0BR1 = 0;
	UCB0I2CSA = LCD_ADDRESS;				// Slave Address
	UCB0CTL1 &= ~UCSWRST;					// Clear SW reset, resume operation
	IE2 |= UCB0TXIE;						// Enable TX interrupt
	IE2 |= UCB0RXIE;						// Enable RX interrupt
	TXByteCnt = 0;							// clear tx/rx counters
	RXByteCnt = 0;
	i2c_stop = 0;							// clear stop
	return;
}


//******************************************************************************
//	Initialization sequence for LCD
//	NOTE: 0xff is a pause command
//
const unsigned char lcd_rs[] = {
	0xe2, 0xff,			// reset
	0xa2,				// ICON  OFF;
	0xa4,				// Entire Display OFF
	0xae,				// Display OFF
	0xc0,				// SHL  select (normal)
	0xa0,				// Reverse direction, ADC=0
//	0xaa,				// ??OSC off
	0xe1,				// Release power save mode
	0xc4,				// DC-DC step-up = (0, 0)
	0x28,				// Power control (VC, VR, VF) = (0, 0, 0)
	0xfe, 0x40, 0x00,	// Set initial display line register
	0xfe, 0x44, 0x00, 	// Set initial COM0 register
	0xfe, 0x48, 0x80,	// Set display ratio: 1/128
	0xfe, 0x4c, 0x00,	// Set N-line inversion 0 (disable)
	0xab,				// OSC on
	0x64, 0xff,			// 3x
	0x65, 0xff,			// 4x
	0x66, 0xff,			// 5x
	0x67, 0xff,			// 6x
	RB_RA,				// RESISTER SET
	0xfe, 0x81, EV,		// Set electronic volume register, n=0~3f
	0x57,				// 1/12 bias
	0x92,				// ??FRC and pwm
	0x2c, 0xff,
//	0x2d, 0xff,
	0x2e, 0xff,
	0x2f, 0xff,
	0x92,				// ??FRC and pwm
	0xfe, 0x38, (FR<<4) + (BE<<2) + EXT,	//	Booster Efficiency BE = (1)

//	start settings for 16-level grayscale
//	0x92,		        // 4frc,60pwm
	0x94,				// 3frc,45pwm
//	0x96,				// 3frc,60pwm

	0xfe, 0x80, 0x00,
	0xfe, 0x81, 0x00,
	0xfe, 0x82, 0x00,
	0xfe, 0x83, 0x00,

	0xfe, 0x84, 0x06,
	0xfe, 0x85, 0x06,
	0xfe, 0x86, 0x06,
	0xfe, 0x87, 0x06,

	0xfe, 0x88, 0x0b,
	0xfe, 0x89, 0x0b,
	0xfe, 0x8a, 0x0b,
	0xfe, 0x8b, 0x0b,

	0xfe, 0x8c, 0x10,
	0xfe, 0x8d, 0x10,
	0xfe, 0x8e, 0x10,
	0xfe, 0x8f, 0x10,

	0xfe, 0x90, 0x15,
	0xfe, 0x91, 0x15,
	0xfe, 0x92, 0x15,
	0xfe, 0x93, 0x15,

	0xfe, 0x94, 0x1a,
	0xfe, 0x95, 0x1a,
	0xfe, 0x96, 0x1a,
	0xfe, 0x97, 0x1a,

	0xfe, 0x98, 0x1e,
	0xfe, 0x99, 0x1e,
	0xfe, 0x9a, 0x1e,
	0xfe, 0x9b, 0x1e,

	0xfe, 0x9c, 0x23,
	0xfe, 0x9d, 0x23,
	0xfe, 0x9e, 0x23,
	0xfe, 0x9f, 0x23,

	0xfe, 0xa0, 0x27,
	0xfe, 0xa1, 0x27,
	0xfe, 0xa2, 0x27,
	0xfe, 0xa3, 0x27,

	0xfe, 0xa4, 0x2b,
	0xfe, 0xa5, 0x2b,
	0xfe, 0xa6, 0x2b,
	0xfe, 0xa7, 0x2b,

	0xfe, 0xa8, 0x2f,
	0xfe, 0xa9, 0x2f,
	0xfe, 0xaa, 0x2f,
	0xfe, 0xab, 0x2f,

	0xfe, 0xac, 0x32,
	0xfe, 0xad, 0x32,
	0xfe, 0xae, 0x32,
	0xfe, 0xaf, 0x32,

	0xfe, 0xb0, 0x35,
	0xfe, 0xb1, 0x35,
	0xfe, 0xb2, 0x35,
	0xfe, 0xb3, 0x35,

	0xfe, 0xb4, 0x38,
	0xfe, 0xb5, 0x38,
	0xfe, 0xb6, 0x38,
	0xfe, 0xb7, 0x38,

	0xfe, 0xb8, 0x3a,
	0xfe, 0xb9, 0x3a,
	0xfe, 0xba, 0x3a,
	0xfe, 0xbb, 0x3a,

	0xfe, 0xbc, 0x3c,
	0xfe, 0xbd, 0x3c,
	0xfe, 0xbe, 0x3c,
	0xfe, 0xbf, 0x3c,

//	end settings for 16-level grayscale
	0x38, 0x74,
//	0xfe, 0x38, (FR<<4) + (BE<<2) + EXT,	//	Booster Efficiency BE = (1)
	0x00
	};

//******************************************************************************
//	initialize lcd display
//
void lcd_init(void)
{
	unsigned char c1;
	unsigned char* dptr = (unsigned char*)lcd_rs;

	i2c_stop = 1;
	while (*dptr)
	{
		switch(*dptr)
		{
			case 0xff:					// delay
				tdelay(2000);
				break;

			case 0xfe:					// 2 byte command
				dptr++;
				c1 = *dptr++;
				LCD_WC2(c1, *dptr);
				break;

			default:
				LCD_WC(*dptr);			// single byte command
				break;
		}
		dptr++;
	}
	lcd_clear();
	lcd_Proportional = 1;
	LCD_WC(0xaf); 	    				//Display ON
	return;
}


//------------------------------------------------------------
//	Turn ON/OFF LCD backlight
//
void lcd_backlight(int backlight)
{
	if (backlight) P2OUT |= 0x10;		// turn on backlight
	else P2OUT &= ~0x10;				// turn off backlight
	return;
}


//------------------------------------------------------------
//	delay routines
void tdelay(unsigned int time)
{
	while(time-- > 0);					// count down to zero
}

void wait(unsigned int time)
{
	int i;
	for (i=0; i<time; i++) tdelay(2000);
}


//-------------------------------------------------------------
//	write single command to LCD
void LCD_WC(unsigned char datum)
{
	P1OUT |= 0x01;						// Turn on P1.0
	while (UCB0CTL1 & UCTXSTP);			// Ensure stop condition got sent
	UCB0I2CSA = LCD_ADDRESS;			// Slave Address

	TXByteCnt = 2;						// Load TX byte counter
	TxData_ptr = TXData;
	TXData[0] = 0x00;					// Co=0, A0=0
	TXData[1] = datum;

	i2c_stop = 1;
	UCB0CTL1 |= UCTR + UCTXSTT;			// I2C TX, start condition
	__bis_SR_register(CPUOFF + GIE);	// Enter LPM0 w/ interrupts
	P1OUT &= ~0x01;						// Turn off P1.0
	return;
}


//-------------------------------------------------------------
//	write double command to LCD
void LCD_WC2(unsigned char datum1, unsigned char datum2)
{
	P1OUT |= 0x01;						// Turn on P1.0
	while (UCB0CTL1 & UCTXSTP);			// Ensure stop condition got sent
	UCB0I2CSA = LCD_ADDRESS;			// Slave Address

	TXByteCnt = 4;						// Load TX byte counter
	TxData_ptr = TXData;
	TXData[0] = 0x80;					// Co=1, A0=0
	TXData[1] = datum1;
	TXData[2] = 0x00;					// Co=0, A0=0
	TXData[3] = datum2;

	i2c_stop = 1;
	UCB0CTL1 |= UCTR + UCTXSTT;			// I2C TX, start condition
	__bis_SR_register(CPUOFF + GIE);	// Enter LPM0 w/ interrupts
	P1OUT &= ~0x01;						// Turn off P1.0
	return;
}


//-------------------------------------------------------------
//	write data to LCD
void LCD_WD(unsigned char datum)
{
	P1OUT |= 0x01;						// Turn on P1.0
	while (UCB0CTL1 & UCTXSTP);			// Ensure stop condition got sent
	UCB0I2CSA = LCD_ADDRESS;			// Slave Address

	TXByteCnt = 8;						// Load TX byte counter
	TxData_ptr = TXData;
	TXData[0] = 0xc0;					// Co=1, A0=1
	TXData[1] = datum;
	TXData[2] = 0xc0;					// Co=1, A0=1
	TXData[3] = datum;
	TXData[4] = 0xc0;					// Co=1, A0=1
	TXData[5] = datum;
	TXData[6] = 0x40;					// Co=0, A0=1
	TXData[7] = datum;

	i2c_stop = 1;
	UCB0CTL1 |= UCTR + UCTXSTT;			// I2C TX, start condition
	__bis_SR_register(CPUOFF + GIE);	// Enter LPM0 w/ interrupts
	P1OUT &= ~0x01;						// Turn off P1.0
	return;
}


//-------------------------------------------------------------
//	clear LCD memory
void lcd_clear(void)
{
	int page, column;

	for (page = MIN_PAGE; page <= MAX_PAGE; page++)
	{
		LCD_WC(page);				// set page
		LCD_WC2(0x01, 0x00);
		for (column = 0; column < HD_X_MAX; column++)
		{
			LCD_WD(0x00);			// zero display memory
		}
	}
	// reset LCD global variables
	lcd_X = 0;
	lcd_Y = 0;
	lcd_Page = 0;
	return;
}


//******************************************************************************
//	Display Image
//
//	IN:		const unsigned char* image	pointer to image
//			int column,					start column (0-129)
//			int page,					start page (12-0)
//			int width,					width of image in pixels (# of bytes/page)
//			int height,					height of image in pixels (multiple of 8)
//
//	        0(0x00) - 159(0x9f)
//	99(0x0c)
//	98(0x0c)
//	97(0x0c)
//	96(0x0c)
//	95(0x0b)
//	94(0x0b)
//	93(0x0b)
//	...
//	10(0x01)
//	09(0x01)
//	08(0x01)
//	07(0x00)
//	06(0x00)
//	05(0x00)
//	04(0x00)
//	03(0x00)
//	02(0x00)
//	01(0x00)
//	00(0x00)
//
void lcd_image(const unsigned char* image, int column, int page, int width, int height)
{
	U8 x, p;

	for (p = page; p >= (page - ((height-1)>>3)); p--)
	{
		LCD_WC(MIN_PAGE + p);					// set page
		LCD_WC2(0x10 + (column>>4), column%16);	// set column
		for (x=0; x < width; x++)
		{
			LCD_WD(*image++);					// output image
		}
	}
	return;
}



//****************************************************************************//
//		  ^
//		  ^
//		  y (0 - 63)
//		  ^
//		  ^
//		0,0 >  >  x (0-129)  >  >
//
void lcd_MoveTo(int x, int y)
{
	lcd_Y = HD_Y_MAX - (y % HD_Y_MAX);
	lcd_X = x % HD_X_MAX;
	lcd_Page = y >> 3;

	LCD_WC(MIN_PAGE + lcd_Page);		// set page
 	LCD_WC(0x10 + (lcd_X >> 4));		// set col = x
	LCD_WC(lcd_X % 16);
	return;
}



//****************************************************************
//****************************************************************

//******************************************************************************
//	ASCII character set for LCD
//
const unsigned char cs[][5] = {
//	-----  -XX--  XX-XX  -----  -X---  XX--X  -X---  -XX--
//	-----  -XX--  XX-XX  -X-X-  -XXX-  XX--X  X-X--  -XX--
//	-----  -XX--  X--X-  XXXXX  X----  ---X-  X-X--  -----
//	-----  -XX--  -----  -X-X-  -XX--  --X--  -X---  -----
//	-----  -XX--  -----  -X-X-  ---X-  -X---  X-X-X  -----
//	-----  -----  -----  XXXXX  XXX--  X--XX  X--X-  -----
//	-----  -XX--  -----  -X-X-  --X--  X--XX  -XX-X  -----
//	-----  -----  -----  -----  -----  -----  -----  -----
	{ 0x00,0x00,0x00,0x00,0x00 },		// SP
	{ 0xfa,0xfa,0x00,0x00,0x00 },		// !
	{ 0xe0,0xc0,0x00,0xe0,0xc0 },		// "
	{ 0x24,0x7e,0x24,0x7e,0x24 },		// #
	{ 0x24,0xd4,0x56,0x48,0x00 },		// $
	{ 0xc6,0xc8,0x10,0x26,0xc6 },		// %
	{ 0x6c,0x92,0x6a,0x04,0x0a },		// &
	{ 0xc0,0xc0,0x00,0x00,0x00 },		// '

//	---X-  -X---  -----  -----  -----  -----  -----  -----
//	--X--  --X--  -X-X-  --X--  -----  -----  -----  ----X
//	--X--  --X--  -XXX-  --X--  -----  -----  -----  ---X-
//	--X--  --X--  XXXXX  XXXXX  -----  XXXXX  -----  --X--
//	--X--  --X--  -XXX-  --X--  -----  -----  -----  -X---
//	--X--  --X--  -X-X-  --X--  -XX--  -----  -XX--  X----
//	---X-  -X---  -----  -----  -XX--  -----  -XX--  -----
//	-----  -----  -----  -----  -X---  -----  -----  -----
	{ 0x7c,0x82,0x00,0x00,0x00 },		// (
	{ 0x82,0x7c,0x00,0x00,0x00 },		// )
	{ 0x10,0x7c,0x38,0x7c,0x10 },		// #
	{ 0x10,0x10,0x7c,0x10,0x10 },		// +
	{ 0x07,0x06,0x00,0x00,0x00 },		// ,
	{ 0x10,0x10,0x10,0x10,0x10 },		// -
	{ 0x06,0x06,0x00,0x00,0x00 },		// .
	{ 0x04,0x08,0x10,0x20,0x40 },		// slash

//	-XXX-  --X--  -XXX-  -XXX-  ---X-  XXXXX  --XXX  XXXXX
//	X---X  -XX--  X---X  X---X  --XX-  X----  -X---  ----X
//	X--XX  --X--  ----X  ----X  -X-X-  X----  X----  ---X-
//	X-X-X  --X--  --XX-  -XXX-  X--X-  XXXX-  XXXX-  --X--
//	XX--X  --X--  -X---  ----X  XXXXX  ----X  X---X  -X---
//	X---X  --X--  X----  X---X  ---X-  X---X  X---X  -X---
//	-XXX-  -XXX-  XXXXX  -XXX-  ---X-  -XXX-  -XXX-  -X---
//	-----  -----  -----  -----  -----  -----  -----  -----
	{ 0x7c,0x8a,0x92,0xa2,0x7c },		// 0
	{ 0x42,0xfe,0x02,0x00,0x00 },		// 1
	{ 0x46,0x8a,0x92,0x92,0x62 },		// 2
	{ 0x44,0x92,0x92,0x92,0x6c },		// 3
	{ 0x18,0x28,0x48,0xfe,0x08 },		// 4
	{ 0xf4,0x92,0x92,0x92,0x8c },		// 5
	{ 0x3c,0x52,0x92,0x92,0x8c },		// 6
	{ 0x80,0x8e,0x90,0xa0,0xc0 },		// 7

//	-XXX-  -XXX-  -----  -----  ---X-  -----  -X---  -XXX-
//	X---X  X---X  -----  -----  --X--  -----  --X--  X---X
//	X---X  X---X  -XX--  -XX--  -X---  XXXXX  ---X-  X---X
//	-XXX-  -XXXX  -XX--  -XX--  X----  -----  ----X  --XX-
//	X---X  ----X  -----  -----  -X---  -----  ---X-  --X--
//	X---X  ---X-  -XX--  -XX--  --X--  XXXXX  --X--  -----
//	-XXX-  -XX--  -XX--  -XX--  ---X-  -----  -X---  --X--
//	-----  -----  -----  -X---  -----  -----  -----  -----
	{ 0x6c,0x92,0x92,0x92,0x6c },		// 8
	{ 0x60,0x92,0x92,0x94,0x78 },		// 9
	{ 0x36,0x36,0x00,0x00,0x00 },		// :
	{ 0x37,0x36,0x00,0x00,0x00 },		// ;
	{ 0x10,0x28,0x44,0x82,0x00 },		// <
	{ 0x24,0x24,0x24,0x24,0x24 },		// =
	{ 0x82,0x44,0x28,0x10,0x00 },		// >
	{ 0x60,0x80,0x9a,0x90,0x60 },		// ?

//	-XXX-  -XXX-  XXXX-  -XXX-  XXXX-  XXXXX  XXXXX  -XXX-
//	X---X  X---X  X---X  X---X  X---X  X----  X----  X---X
//	X-XXX  X---X  X---X  X----  X---X  X----  X----  X----
//	X-X-X  XXXXX  XXXX-  X----  X---X  XXXX-  XXXX-  X-XXX
//	X-XXX  X---X  X---X  X----  X---X  X----  X----  X---X
//	X----  X---X  X---X  X---X  X---X  X----  X----  X---X
//	-XXX-  X---X  XXXX-  -XXX-  XXXX   XXXXX  X----  -XXX-
//	-----  -----  -----  -----  -----  -----  -----  -----
	{ 0x7c,0x82,0xba,0xaa,0x78 },		// @
	{ 0x7e,0x90,0x90,0x90,0x7e },		// A
	{ 0xfe,0x92,0x92,0x92,0x6c },		// B
	{ 0x7c,0x82,0x82,0x82,0x44 },		// C
	{ 0xfe,0x82,0x82,0x82,0x7c },		// D
	{ 0xfe,0x92,0x92,0x92,0x82 },		// E
	{ 0xfe,0x90,0x90,0x90,0x80 },		// F
	{ 0x7c,0x82,0x92,0x92,0x5c },		// G

//	X---X  -XXX-  ----X  X---X  X----  X---X  X---X  -XXX-
//	X---X  --X--  ----X  X--X-  X----  XX-XX  XX--X  X---X
//	X---X  --X--  ----X  X-X--  X----  X-X-X  X-X-X  X---X
//	XXXXX  --X--  ----X  XX---  X----  X---X  X--XX  X---X
//	X---X  --X--  X---X  X-X--  X----  X---X  X---X  X---X
//	X---X  --X--  X---X  X--X-  X----  X---X  X---X  X---X
//	X---X  -XXX-  -XXX-  X---X  XXXXX  X---X  X---X  -XXX-
//	-----  -----  -----  -----  -----  -----  -----  -----
	{ 0xfe,0x10,0x10,0x10,0xfe },		// H
	{ 0x82,0xfe,0x82,0x00,0x00 },		// I
	{ 0x0c,0x02,0x02,0x02,0xfc },		// J
	{ 0xfe,0x10,0x28,0x44,0x82 },		// K
	{ 0xfe,0x02,0x02,0x02,0x02 },		// L
	{ 0xfe,0x40,0x20,0x40,0xfe },		// M
	{ 0xfe,0x40,0x20,0x10,0xfe },		// N
	{ 0x7c,0x82,0x82,0x82,0x7c },		// O

//	XXXX-  -XXX-  XXXX-  -XXX-  XXXXX  X---X  X---X  X---X
//	X---X  X---X  X---X  X---X  --X--  X---X  X---X  X---X
//	X---X  X---X  X---X  X----  --X--  X---X  X---X  X-X-X
//	XXXX-  X-X-X  XXXX-  -XXX-  --X--  X---X  X---X  X-X-X
//	X----  X--XX  X--X-  ----X  --X--  X---X  X---X  X-X-X
//	X----  X--X-  X---X  X---X  --X--  X---X  -X-X-  X-X-X
//	X----  -XX-X  X---X  -XXX-  --X--  -XXX-  --X--  -X-X-
//	-----  -----  -----  -----  -----  -----  -----  -----
	{ 0xfe,0x90,0x90,0x90,0x60 },		// P
	{ 0x7c,0x82,0x92,0x8c,0x7a },		// Q
	{ 0xfe,0x90,0x90,0x98,0x66 },		// R
	{ 0x64,0x92,0x92,0x92,0x4c },		// S
	{ 0x80,0x80,0xfe,0x80,0x80 },		// T
	{ 0xfc,0x02,0x02,0x02,0xfc },		// U
	{ 0xf8,0x04,0x02,0x04,0xf8 },		// V
	{ 0xfc,0x02,0x3c,0x02,0xfc },		// W

//	X---X  X---X  XXXXX  -XXX-  -----  -XXX-  --X--  -----
//	X---X  X---X  ----X  -X---  X----  ---X-  -X-X-  -----
//	-X-X-  X---X  ---X-  -X---  -X---  ---X-  X---X  -----
//	--X--  -X-X-  --X--  -X---  --X--  ---X-  -----  -----
//	-X-X-  --X--  -X---  -X---  ---X-  ---X-  -----  -----
//	X---X  --X--  X----  -X---  ----X  ---X-  -----  -----
//	X---X  --X--  XXXXX  -XXX-  -----  -XXX-  -----  XXXXX
//	-----  -----  -----  -----  -----  -----  -----  -----
	{ 0xc6,0x28,0x10,0x28,0xc6 },		// X
	{ 0xe0,0x10,0x0e,0x10,0xe0 },		// Y
	{ 0x86,0x8a,0x92,0xa2,0xc2 },		// Z
	{ 0xfe,0x82,0x82,0x00,0x00 },		// [
	{ 0x40,0x20,0x10,0x08,0x04 },		// back slash
	{ 0x82,0x82,0xfe,0x00,0x00 },		// ]
	{ 0x20,0x40,0x80,0x40,0x20 },		// ^
	{ 0x02,0x02,0x02,0x02,0x02 },		// _

//	-XX--  -----  X----  -----  ----X  -----  --XXX  -----
//	-XX--  -----  X----  -----  ----X  -----  -X---  -----
//	--X--  -XXX-  XXXX-  -XXX-  -XXXX  -XXX-  -X---  -XXXX
//	-----  ----X  X---X  X---X  X---X  X---X  XXXX-  X---X
//	-----  -XXXX  X---X  X----  X---X  XXXX-  -X---  X---X
//	-----  X---X  X---X  X---X  X---X  X----  -X---  -XXXX
//	-----  -XXXX  XXXX-  -XXX-  -XXXX  -XXX-  -X---  ----X
//	-----  -----  -----  -----  -----  -----  -----  -XXX-
	{ 0xc0,0xe0,0x00,0x00,0x00 },		// `
	{ 0x04,0x2a,0x2a,0x2a,0x1e },		// a
	{ 0xfe,0x22,0x22,0x22,0x1c },		// b
	{ 0x1c,0x22,0x22,0x22,0x14 },		// c
	{ 0x1c,0x22,0x22,0x22,0xfc },		// d
	{ 0x1c,0x2a,0x2a,0x2a,0x10 },		// e
	{ 0x10,0x7e,0x90,0x90,0x80 },		// f
	{ 0x18,0x25,0x25,0x25,0x3e },		// g

//	X----  -X---  ----X  X----  X----  -----  -----  -----
//	X----  -----  -----  X----  X----  -----  -----  -----
//	X----  -X---  ---XX  X--X-  X----  XX-X-  XXXX-  -XXX-
//	XXXX-  -X---  ----X  X-X--  X----  X-X-X  X---X  X---X
//	X---X  -X---  ----X  XX---  X----  X-X-X  X---X  X---X
//	X---X  -X---  ----X  X-X--  X----  X---X  X---X  X---X
//	X---X  -XX--  X---X  X--X-  XX---  X---X  X---X  -XXX-
//	-----  -----  -XXX-  -----  -----  -----  -----  -----
	{ 0xfe,0x10,0x10,0x10,0x0e },		// h
	{ 0xbe,0x02,0x00,0x00,0x00 },		// i
	{ 0x02,0x01,0x01,0x21,0xbe },		// j
	{ 0xfe,0x08,0x14,0x22,0x00 },		// k
	{ 0xfe,0x02,0x00,0x00,0x00 },		// l
	{ 0x3e,0x20,0x18,0x20,0x1e },		// m
	{ 0x3e,0x20,0x20,0x20,0x1e },		// n
	{ 0x1c,0x22,0x22,0x22,0x1c },		// o

//	-----  -----  -----  -----  -----  -----  -----  -----
//	-----  -----  -----  -----  -X---  -----  -----  -----
//	XXXX-  -XXXX  X-XX-  -XXX-  XXXX-  X--X-  X---X  X---X
//	X---X  X---X  -X--X  X----  -X---  X--X-  X---X  X---X
//	X---X  X---X  -X---  -XXX-  -X---  X--X-  X---X  X-X-X
//	X---X  X---X  -X---  ----X  -X--X  X-XX-  -X-X-  XXXXX
//	XXXX-  -XXXX  XXX--  XXXX-  --XX-  -X-X-  --X--  -X-X-
//	X----  ----X  -----  -----  -----  -----  -----  -----
	{ 0x3f,0x22,0x22,0x22,0x1c },		// p
	{ 0x1c,0x22,0x22,0x22,0x3f },		// q
	{ 0x22,0x1e,0x22,0x20,0x10 },		// r
	{ 0x12,0x2a,0x2a,0x2a,0x04 },		// s
	{ 0x20,0x7c,0x22,0x22,0x04 },		// t
	{ 0x3c,0x02,0x04,0x3e,0x00 },		// u
	{ 0x38,0x04,0x02,0x04,0x38 },		// v
	{ 0x3c,0x06,0x0c,0x06,0x3c },		// w

//	-----  -----  -----  ---XX  --X--  XX---  -X-X-  -----
//	-----  -----  -----  --X--  --X--  --X--  X-X--  -----
//	X---X  X--X-  XXXX-  --X--  --X--  --X--  -----  -----
//	-X-X-  X--X-  ---X-  -XX--  -----  --XX-  -----  -----
//	--X--  X--X-  -XX--  --X--  --X--  --X--  -----  --X--
//	-X-X-  -XXX-  X----  --X--  --X--  --X--  -----  -X-X-
//	X---X  --X--  XXXX-  ---XX  --X--  XX---  -----  XXXXX
//	-----  XX---  -----  -----  -----  -----  -----  -----
	{ 0x22,0x14,0x08,0x14,0x22 },		// x
	{ 0x39,0x05,0x06,0x3c,0x00 },		// y
	{ 0x26,0x2a,0x2a,0x32,0x00 },		// z
	{ 0x10,0x7c,0x82,0x82,0x00 },		// {
	{ 0xee,0x00,0x00,0x00,0x00 },		// |
	{ 0x82,0x82,0x7c,0x10,0x00 },		// }
	{ 0x40,0x80,0x40,0x80,0x00 },		// ~
	{ 0x02,0x06,0x0a,0x06,0x02 }		// _
};

char lcd_putchar(char c)
{
	int i;

	if (c == '\n')
	{
		lcd_Page = (lcd_Page-1) % ((MAX_PAGE+1)&0x0f);
		LCD_WC(MIN_PAGE + lcd_Page);	// set page
	 	LCD_WC2(0x10, 0x00);			// set col = 0

	}
	else if (c == '\r')
	{
	 	LCD_WC2(0x10, 0x00);			// set col = 0
	}
	else if ((c >= ' ') && (c <= '~'))
	{
		for (i=0; i<5;)
		{
			LCD_WD(cs[c - ' '][i++]);
			// check proportional flag
			if (lcd_Proportional && !cs[c - ' '][i]) break;
		}
		LCD_WD(0x00);					// 2 columns of blank
		LCD_WD(0x00);
	}
	return c;
} // end my_putchar



//****************************************************************
void lcd_printf(char* fmt, ...)
{
	va_list arg_ptr;
	char* s = pBuffer;

	if (strlen(fmt) > PRINT_BUFFER_SIZE) ERROR2(PRINT_ERROR);
	va_start(arg_ptr, fmt);

	vsprintf(pBuffer, fmt, arg_ptr);
	while (*s) lcd_putchar(*s++);
	va_end(arg_ptr);
	return;
} // end lcd_printf



//****************************************************************
void ERROR2(int error)
{
	__bic_SR_register(GIE);			// disable interrupts
	while (1)
	{
		int i = 0;
		while (--i);
		P1OUT ^= 0x03;
	}
}


//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCnt with the byte count. Also, TXData
// points to the next byte to transmit.
//------------------------------------------------------------------------------

__interrupt void USCIAB0TX_ISR(void);
#pragma vector = USCIAB0TX_VECTOR

__interrupt void USCIAB0TX_ISR(void)
{
	if (TXByteCnt)                            	// Check TX byte counter
	{
		UCB0TXBUF = *TxData_ptr++;              // Load TX buffer (Clear USCI_B0 TX)
		TXByteCnt--;                            // Decrement TX byte counter
	}
	else if (i2c_stop)
	{
		UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
//		IFG2 &= ~UCB0RXIFG;                     // Clear USCI_B0 RX int flag
		IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
		__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
	}
	else if (RXByteCnt)
	{
		*TxData_ptr++ = UCB0RXBUF;				// read data
 		if (--RXByteCnt == 0)					// one more read?
		{
			UCB0CTL1 |= UCTXSTP;                // y, set I2C stop condition
			IFG2 &= ~UCB0RXIFG;                 // Clear USCI_B0 RX int flag
			__bic_SR_register_on_exit(CPUOFF);  // Exit LPM0
		}
	}
/*
	else
	{
		*TxData_ptr++ = UCB0RXBUF;				// read data
		UCB0CTL1 |= UCTXSTP;                // y, set I2C stop condition
		i2c_stop = 1;
		__bic_SR_register_on_exit(CPUOFF);  // Exit LPM0
	}
*/

}


__interrupt void USCIAB0RX_ISR(void);
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	// should not come here!!!!!!!
	ERROR2(USCIAB0RX_ISR_ERROR);
	__bic_SR_register_on_exit(CPUOFF);      	// Exit LPM0
}
