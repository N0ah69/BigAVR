/*
 * ADC.c
 *
 * Created: 16-Mar-20 11:28:31
 *  Author: Pascal Holthuijsen & Joëlle de Vries
 */ 

void ADC_init()
{
	ADMUX  = 0b11100000;
	ADCSRA = 0b10000110;//still need to work out what bits are to be turned on
	DDRF = 0x00;
}

uint8_t Request_ADC_Read()
{
	ADCSRA ^= (1<<6);
	
	while(ADCSRA & (1<<6));
	
	return ADCH;
}
