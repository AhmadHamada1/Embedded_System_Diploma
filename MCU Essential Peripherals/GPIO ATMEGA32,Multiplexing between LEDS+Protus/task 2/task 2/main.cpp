/*
 * task 2.cpp
 *
 * Created: 12/20/2022 7:45:38 PM
 * Author : madaa
 */ 

#include <avr/io.h>
#include "memorymap.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	unsigned int i;
	//unsigned int x;
	DDRA=0b11111111 ;
	clearbit(DDRC,0);
	setbit(PORTC,0);
	
	while (1)
	{
		
		//for(i=0;i<8;i++)
		//{}
			
			if(readbit(PINC,0) ==0)
			{
				setbit(PORTA,i);
				_delay_ms(250);	
			i++;
			}
		
	}
}

