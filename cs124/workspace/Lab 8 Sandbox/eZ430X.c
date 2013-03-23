//	eZ430X.c - eZ430X REV C board system functions
//******************************************************************************
//******************************************************************************
//	        ZZZZZZZZ     44     3333      0000    XX    XX
//	             ZZ     444    33  33    00  00    XX  XX
//	 eeee       ZZ     4444         33  00    00    XXXX           ccccc
//	ee  ee     ZZ     44 44      3333   00    00     XX           cc   cc
//	eeeee     ZZ     44444444       33  00    00    XXXX         cc
//	ee       ZZ          44    33  33    00  00    XX  XX   xxx   cc   cc
//	 eeee   ZZZZZZZZ     44     3333      0000    XX    XX  xxx    ccccc
//******************************************************************************
//******************************************************************************
//	Author:			Paul Roper
//	Revision:		1.0		02/15/2010
//
//	Description:	Initialization firmware for eZ430X Development Board
//
//	See eZ430X.h for eZ430X and i2c prototypes
//
//******************************************************************************
//******************************************************************************
#include <setjmp.h>
#include "msp430x22x4.h"
#include "eZ430x.h"

static void tdelay(unsigned int time);
void init_USCI_B0(int address);

//******************************************************************************
//******************************************************************************
//	LCD Global variables (NOT ZERO'D!!!)
//
jmp_buf i2c_context;			// error context
int i2c_fSCL;					// i2c timing constant
unsigned char TXData[8];		// i2c tx buffer

//******************************************************************************
//	Initialization sequence for eZ430X MSP430F2274
//
int eZ430X_init(int clock)
{
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
		i2c_fSCL = 24;						// 8.0 MHz fSCL = SMCLK/24 = ~333 kHz
	}
	else
	{
		BCSCTL1 = CALBC1_1MHZ;				// Set range 1MHz
		DCOCTL = CALDCO_1MHZ;				// Set DCO step + modulation
		i2c_fSCL = 12;						// 1.2 MHz fSCL = SMCLK/12 = ~100kHz
	}

	// eZ430 red & green leds
	P1DIR = 0x03;							// P1.0, P1.1 output, P1.2 input
	P1OUT &= ~0x03;							// turn off

	// eZ430X push buttons
	P2SEL = 0;								// select GPIO
	P2DIR = 0xd0;							// Configure P2.0-3 as Inputs
	P2OUT = 0x0f;							// use pull-ups
	P2IES = 0x0f;							// high to low transition
	P2REN = 0x0f;							// Enable pull-ups

	// configure eZ430X LED's
//	P2SEL &= ~0xc0;							// select GPIO (P2.6, P2.7)
//	P2DIR |= 0xd0;							// backlight / LED_2 / LED_1
	P2OUT &= ~0xd0;							// turn off
	P3DIR |= 0x08;							// LED_3
	P3OUT &= ~0x08;							// turn off
	P4DIR |= 0x40;							// LED_4
	P4OUT &= ~0x40;

	// configure speaker (P4.5)
	P4DIR |= 0x20;							// speaker

	// configure USCI_B0 for i2c operations
	//		P3.0/UCB0STE	output (used for LCD reset)
	//      P3.1/UCB0SDA	input
	//	    P3.2/UCB0SCL	output
	//      P3.3/UCB0CLK	output (not used)
	P3DIR |= 0x0d;							// P3.0, P3,2, P3,3 outputs
	P3SEL |= 0x0e;                          // SCA, SCL, CLK USCI_B0 option select
	P3OUT &= ~0x01;							// ~CS (also reset LCD)
	wait(10);								// delay
	P3OUT |= 0x01;							// bring high
	P3SEL = 0x06;							// Assign I2C pins to USCI_B0

	// USCI_B0 for i2c
	init_USCI_B0(LCD_ADDRESS);
	return 0;
} // end eZ430X_init


//******************************************************************************
//	Init Universal Synchronous Controller
//
void init_USCI_B0(int address)
{
	UCB0CTL1 |= UCSWRST;					// Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;	// I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_3 + UCSWRST;			// Use SMCLK, keep SW reset
	UCB0BR0 = i2c_fSCL;						// 1.2 MHz fSCL = SMCLK/12 = ~200kHz
	UCB0BR1 = 0;
	UCB0I2CSA = address;					// Slave Address
	UCB0STAT = 0;
	UCB0CTL1 &= ~UCSWRST;					// Clear SW reset, resume operation
	return;
} // init_USCI_B0


//******************************************************************************
//	write data to i2c address
//
//	IN:	address = i2c address
//		  *data = data array
//		  bytes = # of bytes to write
//
//	longjmp's to i2c_context on error
//
void i2c_write(unsigned int address, unsigned char* data, int bytes)
{
	int timeout;

	P1OUT |= 0x01;						// Turn on P1.0

	// Ensure stop condition got sent
	timeout = 1;
	while ((UCB0CTL1 & UCTXSTP) && ++timeout);
	if (timeout == 0)
		// ERROR2(SYS_ERR_I2C_TO1);
		longjmp(i2c_context, SYS_ERR_I2C_TO1);

	UCB0I2CSA = address;				// Slave Address
	UCB0CTL1 |= UCTR + UCTXSTT;			// I2C TX, start condition
	while (bytes--)
	{
		// wait for start to be sent or data to more to shift register
		timeout = 1;
		while (!(IFG2 & UCB0TXIFG) && ++timeout);
		if (timeout == 0)
			// ERROR2(SYS_ERR_I2C_TO2);
			longjmp(i2c_context, SYS_ERR_I2C_TO2);

		UCB0TXBUF = *data++;			// Load TX buffer
		if (bytes == 0)
		{
			// wait for start to be sent or data to more to shift register
			timeout = 1;
			while (!(IFG2 & UCB0TXIFG) && ++timeout);
			if (timeout == 0)
				// ERROR2(SYS_ERR_I2C_TO3);
				longjmp(i2c_context, SYS_ERR_I2C_TO3);

			UCB0CTL1 |= UCTXSTP;		// generate stop on next ack
			IFG2 &= ~UCB0TXIFG;			// Clear USCI_B0 TX int flag
		}
	}
	// Ensure stop condition got sent
	timeout = 1;
	while ((UCB0CTL1 & UCTXSTP) && ++timeout);
	if (timeout == 0)
		// ERROR2(SYS_ERR_I2C_TO1);
		longjmp(i2c_context, SYS_ERR_I2C_TO1);

	P1OUT &= ~0x01;						// Turn off P1.0
	return;
} // end i2c_write


//******************************************************************************
//	read bytes into buffer using i2c
//
void clocklow()
{
	P3OUT &= ~SCL;				// put clock low
	return;
} // end clocklow

void clockhigh()
{
	P3OUT |= SCL;				// put clock high
	return;
} // end clockhigh

unsigned char i2c_read(unsigned int address, unsigned char* buffer, int bytes)
{
	unsigned char i, data;
	unsigned char shift = 0x80;

	LED_RED_ON;
	P3SEL &= ~0x06;				// change SDA & SCL to GPIO pins
	P3DIR |= 0x06;				// set as output

	address = (address << 1) + 1;	// address * 2 + read bit

	P3OUT |= SCL;				// make sure clock is high
	P3OUT &= ~SDA;				// send start condition

	// output 8 bits
	while (shift)
	{
		clocklow();
		if (address & shift)
		{
			P3OUT |= SDA;		// set SDA high
		}
		else
		{
			P3OUT &= ~SDA;		// set SDA low
		}
		clockhigh();
		shift >>= 1;			// adjust mask
	}
	// look for slave ack
	clocklow();
	P3DIR &= ~SDA;				// turn SDA to input
	clockhigh();
	if (P3IN & SDA)				// acknowledge?
	{
		// ERROR2(SYS_ERR_I2C_ACK); // error!
		longjmp(i2c_context, SYS_ERR_I2C_ACK);
	}

	// read 8 bits
	while (bytes--)
	{
		for (i = 0; i < 8; i++)
		{
			clocklow();
			P3DIR &= ~SDA;			// SDA as input
			data <<= 1;				// assume 0
			clockhigh();
			if (P3IN & SDA) data++;
		}
		// save data
		*buffer++ = data;

		// output ack or nack
		if (bytes)
		{
			// output ack
			clocklow();
			P3OUT &= ~SDA;		// ack (0)
			P3DIR |= SDA;		// turn SDA back to output
			clockhigh();
		}
		else
		{
			// done, output nack
			clocklow();
			P3OUT |= SDA;		// nack (1)
			P3DIR |= SDA;		// turn SDA back to output
			clockhigh();
		}
	}

	// stop
	clocklow();
	P3DIR |= SDA;				// make sure SDA is output
	P3OUT &= ~SDA;				// put SDA low
	clockhigh();
	P3OUT |= SDA;				// 1

	P3DIR |= SCL;				// set as outputs
	P3DIR &= ~SDA;				// set as input
	P3SEL |= 0x06;				// re-assign I2C pins to USCI_B0
	LED_RED_OFF;
	return data;
} // end i2c_read


//******************************************************************************
//	delay routines
//
void tdelay(unsigned int time)
{
	while(time-- > 0);					// count down to zero
} // end tdelay

void wait(unsigned int time)
{
	int i;
	for (i=0; i<time; i++) tdelay(2000);
	return;
} // end wait


//******************************************************************************
//	report hard error
//
void ERROR2(int error)
{
	int i, j;

	// return if no error
	if (error == 0) return;

	__bic_SR_register(GIE);			// disable interrupts
	WDTCTL = WDTPW + WDTHOLD;		// Stop WDT
	BCSCTL1 = CALBC1_1MHZ;			// Set range 1MHz
	DCOCTL = CALDCO_1MHZ;			// Set DCO step + modulation

	while (1)
	{
		LED_RED_OFF;
		// pause
		for (i=1; i<4; i++) for (j=1; j; j++);

		// flash LED's 10 times
		i = 10;
		while (i--)
		{
			LED_RED_TOGGLE;
			for (j=1; j<8000; j++);
		}

		LED_RED_OFF;
		// pause
		for (i=1; i<2; i++) for (j=1; j; j++);

		// now blink error #
		for (i = 0; i < error; i++)
		{
			LED_RED_ON;
			for (j=1; j; j++);
			LED_RED_OFF;
			for (j=1; j; j++);
		}
	}
} // end ERROR


//******************************************************************************
//	USCI interrupt service routine
//
__interrupt void USCIAB0RX_ISR(void);
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	// should not come here!!!!!!!
	ERROR2(SYS_ERR_USCB_RX);
	__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
	return;
}

