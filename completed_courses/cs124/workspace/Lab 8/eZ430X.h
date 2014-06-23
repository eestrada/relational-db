//******************************************************************************
//	eZ430X
//******************************************************************************
#ifndef eZ430X_H_
#define eZ430X_H_

#define REV_C	1

//#define WD_CLOCK		32					// WD clock (ms)
//#define WD_1SEC_CNT		1000/WD_CLOCK		// WD counts/second (32 ms)
//#define WD_5SEC_CNT		WD_1SEC_CNT*5		// 5 seconds

#define ON				1
#define OFF				0

#define TRUE			1
#define FALSE			0

typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;

//	system errors
enum SYS_ERRORS {	SYS_ERR_PRINT=1,		// 1 printf line too long
					SYS_ERR_LCD,			// 2 lcd not responding
					SYS_ERR_USCB_RX,		// 3 USCB receive timeout
					SYS_ERR_I2C_TO1,		// 4 i2c timeout
					SYS_ERR_I2C_TO2,		// 5 i2c timeout
					SYS_ERR_I2C_TO3,		// 6 i2c timeout
					SYS_ERR_I2C_ACK,		// 7 i2c ACK timeout
					SYS_ERR_ADC_TO,			// 8 adc timeout
					SYS_ERR_XL345ID			// 9 accelerometer timeout
				};

//******************************************************************************
//	Port 2 equates
#define SW_1		0x01			// P2.0
#define SW_2		0x02			// P2.1
#define SW_3		0x04			// P2.2
#define SW_4		0x08			// P2.3
#define BK_LGT		0x10			// P2.4
#define LED_1		0x40			// P2.6
#define LED_2		0x80			// P2.7

//	Port 3 equates
#define LCD_RST		0x01			// P3.0
#define SDA			0x02			// P3.1 - i2c data
#define SCL			0x04			// P3.2 - i2c clock
#define LED_3		0x08			// P3.3

//	Port 4 equates
#define R_POT		0x08			// P4.3
#define L_POT		0x10			// P4.4
#define SPKR		0x20			// P4.5
#define LED_4		0x40			// P4.6

//******************************************************************************
//	LED's
#define LED_4_ON			P4OUT |= LED_4;
#define LED_4_OFF			P4OUT &= ~LED_4;
#define LED_4_TOGGLE		P4OUT ^= LED_4;

#define LED_3_ON			P3OUT |= LED_3;
#define LED_3_OFF			P3OUT &= ~LED_3;
#define LED_3_TOGGLE		P3OUT ^= LED_3;

#define LED_2_ON			P2OUT |= LED_2;
#define LED_2_OFF			P2OUT &= ~LED_2;
#define LED_2_TOGGLE		P2OUT ^= LED_2;

#define LED_1_ON			P2OUT |= LED_1;
#define LED_1_OFF			P2OUT &= ~LED_1;
#define LED_1_TOGGLE		P2OUT ^= LED_1;

#define LED_RED_ON			P1OUT |= 0x01;
#define LED_RED_OFF			P1OUT &= ~0x01;
#define LED_RED_TOGGLE		P1OUT ^= 0x01;

#define LED_GREEN_ON		P1OUT |= 0x02;
#define LED_GREEN_OFF		P1OUT &= ~0x02;
#define LED_GREEN_TOGGLE	P1OUT ^= 0x02;

//******************************************************************************
//
#define SPEAKER_ON			P4OUT |= SPKR;
#define SPEAKER_OFF			P4OUT &= ~SPKR;
#define SPEAKER_TOGGLE		P4OUT ^= ~SPKR;

#define BACKLIGHT_ON		P2OUT |= BK_LGT;	// turn on backlight
#define BACKLIGHT_OFF		P2OUT &= ~BK_LGT;	// turn off backlight

//	i2c equates
#if REV_C == 1
#define ADXL345_ADR			0x1d				// ADXL345 accelerometer
#else
#define ADXL345_ADR			0x53
#endif
#define LCD_ADDRESS			0x3f				// LCD display
#define FRAM_ADR			0x50				// F-RAM

#define CLOCK_LOW			P3OUT &= ~SCL;		// put clock low
#define CLOCK_HIGH			P3OUT |= SCL;		// put clock high

//******************************************************************************
//	prototypes
//
//	i2c prototypes
void i2c_write(unsigned int address, unsigned char* data, int bytes);
unsigned char i2c_read(unsigned int address, unsigned char* buffer, int bytes);

//	eZ430X prototypes
int eZ430X_init(int clock);
void init_USCI_B0(int i2c_address);
void ERROR2(int error);
void wait(unsigned int time);

//******************************************************************************
#endif /*eZ430X_H_*/

