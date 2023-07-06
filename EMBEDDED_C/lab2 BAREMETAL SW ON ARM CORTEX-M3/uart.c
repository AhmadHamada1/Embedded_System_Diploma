#include "uart.h"

#define UART0DR  *((volatile unsigned int*)((unsigned int*)0x101f1000))

void Uart_send_str(unsigned char *PTStr){

	while(*PTStr != '\0')
	{
		UART0DR = (unsigned int)*PTStr;
		PTStr++;
	}
}
