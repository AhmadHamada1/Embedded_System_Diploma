#include <avr/io.h>
#include "memorymap.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	//unsigned int i;
	//unsigned int x;
	DDRD=0b11111110 ;
	clearbit(DDRD,0);
	setbit(PORTD,0);
	
	while (1)
	{
		
		//for(i=0;i<8;i++)
		//{}
		
		if(readbit(PIND,0) ==1)
		{
			setbit(PORTD,4);
			_delay_ms(50);
			clearbit(PORTD,4);
			
		}
		
	}
}

