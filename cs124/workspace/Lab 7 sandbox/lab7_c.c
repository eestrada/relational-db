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
// INITIALIZE CONSTANTS (FOR TONES)
//
#define CLOCK	8000000					// clock speed
#define WD_1SEC_CNT	CLOCK/32000			// WD counts/second (32 ms)
#define WD_5SEC_CNT	WD_1SEC_CNT*5		// WD counts/5 seconds (32 ms)
#define BLIP_COUNT	8*2000
#define	SEED	256						// choose arbitrary seed for random generator

//------------------------------------------------------------------------------
// INITIALIZE CONSTANTS FOR NOTES
//
/*
#define	C4 CLOCK*1000/261626      // C  (261.626 Hz)
#define CS4 C4*15/16              // C# (minor 2nd)
#define D4 C4*8/9                 // D  (major 2nd)
#define DS4 C4*5/6                // D# (minor 3rd)
#define E4 C4*4/5                 // E  (major 3rd)
#define F4 C4*3/4                 // F  (perfect 4th)
#define FS4 C4*5/7                // F# (diminished 5th)
#define G4 C4*2/3                 // G  (perfect 5th)
#define GS4 C4*5/8                // G# (minor 6th)
#define A4 C4*3/5                 // A  (major 6th)
#define AS4 C4*4/7                // A# (minor 7th)
#define B4 C4*8/15                // B  (major 7th)
#define C5 C4*1/2                 // C  (perfect octave)
#define E5 E4*1/2				  // E
#define C6 C5*1/2                 // C  (perfect octave)
#define C7 C6*1/2                 // C  (perfect octave)	
*/

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
volatile int LCD_BL_wait = 0;

//-----------------------------------------------------------
//	main
void main(void)
{
	int twinDice = 0;

	eZ430X_init(CALDCO_8MHZ);			// init board

	// configure Watchdog for ez430 LED toggle
	WD_Cnt1 = WD_1SEC_CNT;				// set WD 1 second counter
	WDTCTL = WDT_MDLY_32;				// Set Watchdog interval to ~32ms
	IE1 |= WDTIE;						// Enable WDT interrupt
	
	// configure TimerA for tone output
	TACCTL0 = CCIE;						// TACCR0 interrupt enabled
	TACCR0 = BLIP_COUNT;
	TACTL = TASSEL_2 + MC_1;			// SMCLK, up mode

	__bis_SR_register(GIE);				// enable interrupts

	lcd_init();							// init LCD & interrupts
	lcd_clear();
	
	initRand16(SEED);					// init random number generator with a known seed

	while (1)
	{
		int press = 0;					// used to determine if a button has been pressed 
		int rollNum;					// holds number to count down number of dice rolls
		int waitSome = 16;				// how long to wait between die face changes
		int die_A_Rand;					// use to hold face value of die A
		int die_B_Rand;					// use to hold face value of die B
		
		lcd_backlight(1);				// turn on LCD backlight
		LCD_BL_wait = WD_5SEC_CNT;		// initialize LCD backlight counter for 5 seconds; use WDT interupt as timer
		lcd_MoveTo(20, 20);				// set display for refresh
		lcd_printf("Please press a button.");	// print instructions to screen
		
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
		
//		press = 0;						// reset press variable for next time around
		
		lcd_clear();					// clear screen
		
		drawDieFrame(10);				// draw die A frame
		drawDieFrame(90);				// draw die B frame
		
		rollNum = 9 + rand6();			// initialize rollNum to a number from 10-15
				
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
			
			TA0_tone_on = 1;			// turn on tone
			
			wait(waitSome);				// delay for a time
			
			TA0_tone_on = 0;			// turn off tone
			
			lcd_backlight(1);			// turn on LCD backlight
			
			waitSome += 16;				// increase the wait time to "slow" the die roll
		}
		

		
		if (die_A_Rand == die_B_Rand && twinDice == 0)	// are die A and B the same?
		{	
			lcd_MoveTo(60, 20);			// set display for refresh
			lcd_printf("Doubles!");		// print instructions to screen
			
			congratDitty();				// Play a happy tune
			wait(256);					// delay a bit
			
			twinDice = 1;				// use this to check next time around
		}	
		else if (die_A_Rand == die_B_Rand && twinDice == 1) // second time in a row they are the same?
		{
			lcd_MoveTo(40, 20);			// set display for refresh
			lcd_printf("Too many doubles!");		// print instructions to screen
			
			congratDitty();			// Play a happy tune
			wait(256);				// wait for it...wait for it...
			razzDitty();			// now play a rasberry.
			twinDice = 0;			// clear out twinDice for a clean slate next time
		}
		else if (die_A_Rand != die_B_Rand && twinDice == 1)
		{
			twinDice = 0;			// clear out twinDice for a clean slate next time
		}			
	}
}

congratDitty(void)
{
	TA0_tone_on = 1;
	
	TACCR0 = 12000;			// E5
	wait(128);				// quarter note
	TACCR0 = 15000;			// C5
	wait(64);				// eighth note
	TACCR0 = 18000;			// A4
	wait(128);				// quarter note
	TACCR0 = 26666;			// D4
	wait(64);				// eighth note
	TACCR0 = 18000;			// A4
	wait(64);				// eighth note
	TACCR0 = 15000;			// C5
	wait(64);				// eighth note
	TACCR0 = 12000;			// E5
	wait(256);				// half note
	
	TA0_tone_on = 0;
	
	TACCR0 = BLIP_COUNT;
	
//	return;
}

razzDitty(void)
{
	TACCR0 = 15000;			// initialize timer a for to a C5
	TA0_tone_on = 1;
	
	while (TACCR0 < 60000)	//
	{		
		wait(4);
		TACCR0 += 256;
		
	}
	TA0_tone_on = 0;
	TACCR0 = BLIP_COUNT;
	
//	return;
}

//------------------------------------------------------------------------------
// Timer A0 interrupt service routine
#pragma vector = TIMERA0_VECTOR
__interrupt void TIMERA0_ISR(void)
{
	if (TA0_tone_on)
	{
		//TA0_tone_on--;
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
	
	if (LCD_BL_wait == 0)
	{
		;
	}
	else if (LCD_BL_wait-- == 1)
	{
		lcd_backlight(0);			// turn off LCD backlight
	}	
}
