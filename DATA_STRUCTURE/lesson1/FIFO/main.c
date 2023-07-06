/*
 * main.c
 *
 *  Created on: 28 Aug 2022
 *      Author: Dell
 */

#include"fifo.h"

element_type buffer[width];


int main()
{
	FIFO_BUF_t UART_BUF;
	element_type i, temp;
	if(FIFO_INIT(&UART_BUF,buffer,5) == FIFO_NO_ERROR)
		printf("FIFO INIT is done....\n");
	for(i = 0;i < 7;i++)
	{
		if(FIFO_enqueue(&UART_BUF,i) == FIFO_NO_ERROR)
			printf("<%d> is enqueued in the buffer...\n",i);
		else
			printf("<%d> is failed to enqueued in the buffer...\n",i);
	}
	print_FIFO(&UART_BUF);
	if(FIFO_dequeue(&UART_BUF,&temp) == FIFO_NO_ERROR)
		printf("<%d> dequeued from the buffer...\n",temp);
	if(FIFO_dequeue(&UART_BUF,&temp) == FIFO_NO_ERROR)
		printf("<%d> dequeued from the buffer...\n",temp);
	print_FIFO(&UART_BUF);
	return 0;
}
