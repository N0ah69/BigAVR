
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>




/******************************************************************/
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void BlinkLed()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0xff;
	while (1)
	{
		//PORTD = 0xAA;			// Write 10101010b PORTD
		PORTC = 0b10000000;
	
		wait( 500 );
		//PORTD = 0x55;			// Write 01010101b PORTD
		PORTC = 0b01000000;
		wait( 500 );
	}
}

void ButtonC0Pressed()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	while (1)
	{
		if (PINC & 0x01)
		{
			PORTD = 0x80;
			wait(250);
		}
		
		PORTD = 0x00;
		wait(250);
	}
}

void WalkingLight()
{
	DDRE = 0xff;
	int i = 0;
	while(1)
	{
		PORTE = 1 << i;
		i = (i+1)% 8;
		wait(50);
	}
}

/******************************************************************/
int main( void )

{
	
	WalkingLight();

	return 1;
}
