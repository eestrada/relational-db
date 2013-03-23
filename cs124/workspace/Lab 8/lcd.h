//******************************************************************************
//	LCD
//******************************************************************************
#ifndef LCD_H_
#define LCD_H_

#define printf lcd_printf

//	initialization constants
#define EV					24			// LCD volume
#define EXT					1
#define BE					1
#define FR					7
#define RB_RA				0x06 		// internal resistor ratio
//#define RB_RA				0x27

//	display size
#define HD_X_MAX			160
#define HD_Y_MAX			100
#define MIN_PAGE			0xb0
#define MAX_PAGE			0xbc

//	print buffer size
#define PRINT_BUFFER_SIZE	32

//	lcd modes
#define LCD_PROPORTIONAL	0x01
#define LCD_REVERSE_FONT	0x02
#define LCD_2X_FONT			0x04
#define LCD_FRAM_CHARACTER	0x08
#define LCD_REVERSE_DISPLAY	0x10

//	lcd prototypes
int lcd_init(void);
void lcd_clear(int value);
void lcd_backlight(int backlight);
void lcd_volume(int volume);
int lcd_display(int mode);

void lcd_WC(unsigned char cmd);
void lcd_WD(unsigned char datum);
void lcd_WC2(unsigned char cmd1, unsigned char cmd2);

//	lcd character data
char lcd_putchar(char c);
void lcd_printf(char* fmt, ...);
void lcd_cursor(int column, int page);
void lcd_image(const unsigned char* image, int column, int page);
void lcd_blank(int column, int page, int width, int height);

#endif /*LCD_H_*/

