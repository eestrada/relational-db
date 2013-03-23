#ifndef eZ430X_H_
#define eZ430X_H_

#define LED_00	P1.0;		// LED

#define LED_A	0x40			// P4.6
#define LED_B	0x08			// P3.3
#define LED_C	0x80			// P2.7
#define LED_D	0x40			// P2.6

#define HD_X_MAX	160
#define HD_Y_MAX	100

#define MIN_PAGE	0xb0
#define MAX_PAGE	0xbc

#define EXT		1
#define BE		1
#define FR		7
#define EV		6				// LCD volume
#define RB_RA	0x27			// resistor ratio

#define PRINT_BUFFER_SIZE	32
#define PRINT_ERROR			1
#define USCIAB0RX_ISR_ERROR	2

typedef unsigned char U8;
typedef unsigned int U16;

#define LCD_ADDRESS	0x3f
#define ADXL345_ADR	0x53
#define FRAM_ADR	0x50

//******************************************************************************
//	Prototypes

void eX430X_init(int clock);
void ERROR2(int error);

//	LCD Prototypes

void lcd_init(void);
void lcd_clear(void);
void lcd_backlight(int backlight);
void wait(unsigned int time);

void LCD_WC(unsigned char cmd);
void LCD_WD(unsigned char datum);
void LCD_WC2(unsigned char cmd1, unsigned char cmd2);

char lcd_putchar(char c);
void lcd_printf(char* fmt, ...);
void lcd_image(const unsigned char* image, int column, int page, int width, int height);
void lcd_MoveTo(int x, int y);

#endif /*LCD_H_*/
