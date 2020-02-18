/*
 * Week_3.c
 *
 * Created: 12-Feb-20 12:08:02
 * Author : pmhol
 */ 

#include "LCD.h"



void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int msCount = 0;
char isOn = 0;



ISR( TIMER2_COMP_vect )
{
	msCount++; // Increment ms counter
	if ( msCount == 25 && isOn == 0)
	{
		isOn = 1;
		PORTD ^= (1 << 7); // Toggle bit 7 van PORTD
		msCount = 0; // Reset ms_count value
	}
	else if(msCount == 15 && isOn == 1)
	{
		isOn = 0;
		PORTD ^= (1 << 7); // Toggle bit 7 van PORTD
		msCount = 0; // Reset ms_count value
	}
}

void initTimer( void )
{
	OCR2 = 250;
	TIMSK|= (1 << 7);
	TCCR2 = 0x07;
	DDRC = 0xff;
	
}


int main(void)
{
    init_lcd();
	initTimer();
	sei();
	
    while (1) 
    {
		wait(10);
		
		DDRB = 0xFF; // PORTB is output
		PORTB = TCNT2;
		char string[9];
		itoa(TCNT2, string, 9);
		lcd_writeLine1(string);
		wait(100);
		
    }
}

