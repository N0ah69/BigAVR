#include "LCD.h"
#include "Generic.h"

void lcd_command(unsigned char command)  //Function to send command instruction to LCD
{
	PORTC = command & 0xF0; // hoge nibble
	PORTC = PORTC | 0x08; // data (RS=0),
	// start (EN=1)
	_delay_ms(25); // wait 1 ms
	PORTC = 0x04; // stop (EN = 0)
	PORTC = (command & 0x0F) << 4; // lage nibble
	PORTC = PORTC | 0x08; // data (RS=0),
	// start (EN=1)
	_delay_ms(25); // wait 1 ms
	PORTC = 0x00; // stop
	// (EN=0 RS=0)
}

void init_lcd(void)
{
	// return home
	DDRC = 0xff;
	
	_delay_ms(25);
	
	lcd_command( 0x02 );
	_delay_ms(25);
	
	// mode: 4 bits interface data, 2 lines, 5x8 dots
	lcd_command( 0x28 );
	_delay_ms(25);
	
	// display: on, cursor off, blinking off
	lcd_command( 0x0C );
	_delay_ms(25);
	
	// entry mode: cursor to right, no shift
	lcd_command( 0x06 );
	_delay_ms(25);

	// RAM adress: 0, first position, line 1
	lcd_command( 0x80 );
	_delay_ms(25);
	
	lcd_command(0x01);
	_delay_ms(25);
}



void lcd_writeChar( unsigned char dat )
{
	PORTC = dat & 0xF0; // hoge nibble
	PORTC = PORTC | 0x0C; // data (RS=1),
	// start (EN=1)
	_delay_ms(25); // wait 1 ms
	PORTC = 0x04; // stop (EN = 0)
	PORTC = (dat & 0x0F) << 4; // lage nibble
	PORTC = PORTC | 0x0C; // data (RS=1),
	// start (EN=1)
	_delay_ms(25); // wait 1 ms
	PORTC = 0x00; // stop
	// (EN=0 RS=0)
}

void lcd_writeLine1 ( char text1[] )
{
	// eerst de eerste 8 karakters = regel 1
	// eerste pos regel 1
	lcd_command(0x80);
	
	uint8_t strsize = strlen(text1);
	for (uint8_t i=0; i<strsize; i++) {
		lcd_writeChar( text1[i] );
	}
	
}

void lcd_writeLine2 ( char text2[] )
{
	// dan de eerste 8 karakters = regel 2
	// eerste pos regel 2
	uint8_t strsize = strlen(text2);
	for (uint8_t i=0; i<strsize; i++) {
		lcd_writeChar( text2[i] );
	}
}

void lcd_setCursorPosition(int position)
{
	char value;
	if(position >= 16)
	{
		position = position - 16;
		value = 0xc0 + position;
		lcd_command(value);
	}
	else
	{
		value = 0x80 + position;
		lcd_command(value);
	}
}
