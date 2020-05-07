/*
 * Week_4.c
 *
 * Created: 04-Mar-20 14:15:28
 * Author : pmhol
 */ 

#define F_CPU 8e6
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



void wait(int ms){
	for (int i = 0 ; i < ms ; i++){
		_delay_ms(1); 
	}
}

void adcinit( void){
	ADMUX = 0b11100000; 
	ADCSRA = 0b11100110; 
}

void adcinit2()
{
	ADMUX  = 0b11100000;
	ADCSRA = 0b10000110;
}

void B1(void)
{
	/* Replace with your application code */
	DDRF = 0x00;
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcinit();
	
	while (1)
	{
		
		PORTA = ADCH; 
		wait (500);
		
	}
}

void B2()
{
	/* Replace with your application code */
	DDRF = 0x00;
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0x00;
	adcinit2();
	
	PORTD &= ~(1<<0);
	while (1)
	{
		if (PIND == 0x01)
			ADCSRA ^= (1<<6);
			
		//while(ADCSRA & (1<<6));
		
		PORTA = ADCH;
		
		wait (500);
		
	}
}

int main()
{
	B1();
}


