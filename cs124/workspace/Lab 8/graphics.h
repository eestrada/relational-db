#ifndef GRAPHICS_H_
#define GRAPHICS_H_

//******************************************************************************
//	FRAM
//******************************************************************************

#define FRAM_SIZE			8192
#define FRAM_LCD_SIZE		2080		// 13 x 160
#define FRAM_CACHE_SIZE		7

typedef union
{
	unsigned long value;
	struct
	{
		unsigned int addr;
		unsigned char data;
		unsigned char temp;
	} entry;
} FRAM_ENTRY;

//	LCD Prototypes
unsigned char lcd_point(unsigned int x, unsigned int y, int flag);
void lcd_circle(int x0, int y0, int r0);
int lcd_FRAM_init(void);

//	FRAM Prototypes
int FRAM_init(int size, int data);
unsigned char FRAM_read(unsigned int address);
int FRAM_write(unsigned int address, unsigned char datum);

int read_FRAM_point(unsigned int x, unsigned int y);
int write_FRAM_point(unsigned int x, unsigned int y, int value);

#endif /*GRAPHICS_H_*/
