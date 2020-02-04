
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

void Animation()
{
	DDRA = 0b11111111;					// PORTD all output
	DDRB = 0b11111111;					// PORTD all output
	DDRC = 0b11111111;					// PORTD all output
	DDRD = 0b11111111;					// PORTD all output
	DDRE = 0b11111111;					// PORTD all output
	DDRF = 0b11111111;					// PORTD all output
	
	
	
	while (1)
	{
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD
			PORTA = pattern[index].data;
			PORTB = pattern[index].data;
			PORTC = pattern[index].data;
			PORTD = pattern[index].data;
			PORTE = pattern[index].data;
			PORTF = pattern[index].data;
			
			
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
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
	DDRB = 0xff;
	int i = 0;
	while(1)
	{
		PORTB = 1 << i;
		i = (i+1)% 8;
		wait(50);
	}
}

typedef enum {OFF = 0, SLOW = 1, FAST = 2} STATES;

void StateSwitch()
{
	DDRC = 0x00;
	DDRD = 0xff;
	STATES switch1 = OFF;
	while(1)
	{
		if(PINC & 0x01)
		{
			switch1 = (switch1 + 1) % 3;
			
		}
	
		switch(switch1)
		{
			case OFF:
				PORTD = 0x00;
				break;
			case SLOW:
				PORTD = 0x80;
				wait(500);
				PORTD = 0x00;
				wait(500);
				break;
			case FAST:
				PORTD = 0x80;
				wait(200);
				PORTD = 0x00;
				wait(200);
				break;
		}
		
	}
}

void setCharliePlexingLed(int led)
{

	switch (led)
	{
		case 1:
		DDRA = 0b11111011;
		PORTA = 0x01;
		break;
		case 2:
		DDRA = 0b11111011;
		PORTA = 0x02;
		break;
		case 3:
		DDRA = 0b11111110;
		PORTA = 0x02;
		break;
		case 4:
		DDRA = 0b11111110;
		PORTA = 0x04;
		break;
		case 5:
		DDRA = 0b11111101;
		PORTA = 0x04;
		break;
		case 6:
		DDRA = 0b11111101;
		PORTA = 0x01;
		break;
	}
}



/******************************************************************/
int main( void )

{
	
	setCharliePlexingLed(2);
	//DDRA = 0x00;
	return 1;
}
