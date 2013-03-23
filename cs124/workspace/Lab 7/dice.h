#ifndef DICE_H_
#define DICE_H_

#define CLOCK	8000000					// clock speed
#define WD_1SEC_CNT	CLOCK/32000			// WD counts/second (32 ms)
#define WD_5SEC_CNT	WD_1SEC_CNT*5		// WD counts/5 seconds (32 ms)
#define BLIP_COUNT	8*2000
#define	SEED	256						// choose arbitrary seed for random generator

//******************************************************************************
//	Prototypes
congratDitty(void);

razzDitty(void);

#endif /*DICE_H_*/
