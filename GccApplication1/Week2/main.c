/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#include "LCD.h"

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}



ISR( INT0_vect )
{
    //PORTC = 1 << i;
    //i = (i + 1)%8;	
	
	DDRC = 0x00;
	int value = PINC;
	DDRC = 0xff;
	if (value == 0)
	{
		PORTC = 0x01;
	}
	else
	{
		PORTC = value << 1;
	}
		
}


ISR( INT1_vect )
{
	DDRC = 0x00;
	int value = PINC;
	DDRC = 0xff;
	if (value == 0)
	{
		PORTC = 0x01;
	}
	else
	{
		PORTC = value << 1;
	}
}



const unsigned char
NUMBERS[16] =
{
	// dPgfedcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, //a
	0b01111100, //b
	0b00001111, //c
	0b01011110, //d
	0b01111001, //e
	0b01110001, //f
};

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x08, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x80, 200}, {0x40, 200}, {0x20, 200}, {0x10, 200}, {0x08, 100} , {0x04, 200}, {0x02, 200}, {0x01, 200}, {0x00, 200},
	{0x00, 100},
	{0xAA,  70}, {0x55,  50},
	{0xAA,  70}, {0x55,  50},
	{0xAA,  70}, {0x55,  50},
	{0x00, 100},
	{0x03, 100}, {0x06, 100}, {0x0c, 100}, {0x18, 100}, {0x30, 100}, {0x70, 100}, {0b11000000, 100},
	
	
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};


void displayNum(int num)
{
	if (num >= 0 && num <=15)
	{
		PORTD = NUMBERS[num];
	}
	else
	{
		PORTD = NUMBERS[14];
	}
}



int main( void )
{
	// Init I/O
	/*DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input
	DDRC = 0xFF;				// set portC to output for the walking lights	
	
	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();				

	while (1)
	{
		;							
	}

	return 1;*/
	init_lcd();
	//init_lcd();
	_delay_ms(25); 
	
	//lcd_command(0x01); 
	//lcd_writeLine1("abababababa");
	//lcd_setCursorPosition(20);
	

	
	lcd_writeLine1("hey         ");
	//init_lcd(); 
	DDRD = 0xff;
	
	while(1)
	{
		wait(10);
		
	}
	
	

	
}