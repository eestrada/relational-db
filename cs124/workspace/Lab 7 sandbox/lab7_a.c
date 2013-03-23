//******************************************************************************
//  Lab 7 - Dice
//
//  Description:
//
//	"Write a dice roller C program that waits for a switch to be pressed
//	and then displays two dice which randomly change values.  The dice
//	roll begins rapidly and progressively slows down until it stops after
//	approximately 3-5 seconds. A roll of snake eyes (double ones) results
//	in a raspberry tone and double sixes results in a congratulatory ditty.
//	Also, write an assembly language function which returns a random
//	number from 0 to 5 and call this function from your C program." 
//
//	                   MSP430F2274
//	                -----------------
//	            /|\|         XIN P2.6|-->LED_D
//	             | |        XOUT P2.7|-->LED_C
//	             --|RST              |
//                 |     P3.0/UCB0STE|
//                 |     P3.1/UCB0SDA|<-|---+->|P3.1/UCB0SDA  XIN|-
//                 |     P3.2/UCB0SCL|<-+----->|P3.2/UCB0SCL     |
//                 |     P3.3/UCB0CLK|
//	               |                 |
//	     RED LED-->|P1.0         P2.0|<--SW1 (pull-up)
//	   GREEN LED-->|P1.1         P2.1|<--SW2 (pull-up)
//	eZ430 BUTTON-->|P1.2         P2.2|<--SW3 (pull-up)
//	               |             P2.3|<--SW4 (pull-up)
//	               |             P2.4|-->LCD BACKLIGHT
//	               |             P3.3|-->LED_B
//	               |             P4.3|-->LEFT POTENTIOMETER
//	               |             P4.6|-->LED_A
//	               |                 |
//	               |             P4.5|-->BUZZER
//
//
//  Built with Code Composer Essentials Version: 2.0
//******************************************************************************
//
#include "msp430x22x4.h"
#include "stdlib.h"
#include "eZ430X.h"

//------------------------------------------------------------------------------
// INITIALIZE CONSTANTS FOR TONES
//
#define CLOCK	8000000					// clock speed
#define WD_1SEC_CNT	CLOCK/32000			// WD counts/second (32 ms)
#define BLIP_COUNT	8*500
#define	SEED	256						// choose seed for random generator

//-----------------------------------------------------------
//	external references
extern void drawDieFrame(int x);
extern void outDie0(int x);
extern void outDie1(int x);
extern void outDie2(int x);
extern void outDie3(int x);
extern void outDie4(int x);
extern void outDie5(int x);
extern void outDie6(int x);

extern void ERROR2 (int x);

extern void initRand16(int x);			// init random # generator
extern int rand6(void);					// get 0-5 random #

//-----------------------------------------------------------
//	global variables
volatile int WD_Cnt1;
volatile int TA0_tone_on = 0;

//-----------------------------------------------------------
//	main
void main(void)
{
	int twinDice = 0;

	eZ430X_init(CALDCO_8MHZ);			// init board

	// configure Watchdog
	WD_Cnt1 = WD_1SEC_CNT;				// set WD 1 second counter
	WDTCTL = WDT_MDLY_32;				// Set Watchdog interval to ~32ms
	IE1 |= WDTIE;						// Enable WDT interrupt

	// configure TimerA
	TACCTL0 = CCIE;						// TACCR0 interrupt enabled
	TACCR0 = BLIP_COUNT;
	TACTL = TASSEL_2 + MC_1;			// SMCLK, up mode

	__bis_SR_register(GIE);				// enable interrupts

	lcd_init();							// init LCD & interrupts
	lcd_clear();
	
	initRand16(SEED);					// init random number generator with a known seed

	lcd_MoveTo(20, 20);					// set display for refresh
	lcd_printf("Please press a button.");

	while (1)
	{
		int press = 0;					// used to determine if a button has been pressed 
		int rollNum;					// holds number to count down number of dice rolls
		int waitSome = 2;				// how long to wait between die face changes
		int die_A_Rand;					// hold face value of die A
		int die_B_Rand;					// hold face value of die B
		
		while (press == 0)				// loop until button is pressed
		{
			int myInt = P2IN;			// use a local variable to hold state of P2.0-3
			
			myInt &= 0x000f;			// don't look at anything above the first nybble
			myInt ^= 0x0f;				// flip lower nybble (since switches are set high)
			
			if (myInt != 0)				// check for a pressed switch
			{
				press = 1;				// use this to break the while loop
				P2OUT = 0xf;			// make sure all the switches are set high again
				lcd_backlight(1);		// turn on LCD backlight
			}
		}
		
		press = 0;						// reset press variable for next time around
		
		drawDieFrame(10);				// draw die A frame
		drawDieFrame(90);				// draw die B frame
		
		rollNum = 14 + rand6();			// initialize rollNum to a number from 15-20
				
		while (rollNum-- > 0)			// do this loop until rollNum decrements to 0	
		{
			
			die_A_Rand = rand6();
			die_B_Rand = rand6();
			
			if (die_A_Rand == 1)		// find out what die A is and display
			{
				outDie1(18);
			}
			else if (die_A_Rand == 2)
			{
				outDie2(18);
			}
			else if (die_A_Rand == 3)
			{
				outDie3(18);
			}
			else if (die_A_Rand == 4)
			{
				outDie4(18);
			}
			else if (die_A_Rand == 5)
			{
				outDie5(18);
			}
			else if (die_A_Rand == 6)
			{
				outDie6(18);
			}


			
			if (die_B_Rand == 1)		// find out what die B is and display
			{
				outDie1(98);
			}
			else if (die_B_Rand == 2)
			{
				outDie2(98);
			}
			else if (die_B_Rand == 3)
			{
				outDie3(98);
			}
			else if (die_B_Rand == 4)
			{
				outDie4(98);
			}
			else if (die_B_Rand == 5)
			{
				outDie5(98);
			}
			else if (die_B_Rand == 6)
			{
				outDie6(98);
			}
			
			lcd_backlight(0);			// turn off LCD backlight
			
//			TA0_tone_on = 1;			// turn on tone
			
			wait(waitSome);				// delay for a time
			
//			TA0_tone_on = 0;			// turn off tone
			
			lcd_backlight(1);			// turn on LCD backlight
			
			waitSome *= waitSome;			
		}
		

		
		
		if (die_A_Rand == die_B_Rand)
		{	
			//congratDitty();
			
			if (twinDice == 1)
			{
				//razzDitty();
				twinDice = 0;
			}
			else
			{
				twinDice = 1;
			}
		}	
	}
}


// Timer A0 interrupt service routine
#pragma vector = TIMERA0_VECTOR
__interrupt void TIMERA0_ISR(void)
{
	if (TA0_tone_on)
	{
		TA0_tone_on--;
		P4OUT ^= 0x20;
	}
}


//------------------------------------------------------------------------------
//	Watchdog Timer ISR
//
__interrupt void WDT_ISR(void);
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	if (--WD_Cnt1 == 0)
	{
		P1OUT ^= 0x02;				// Toggle Port P1.1
		WD_Cnt1 = WD_1SEC_CNT;		// reset counter
	}
}
