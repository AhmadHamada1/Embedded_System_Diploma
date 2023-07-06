/*
 * fifo.c
 *
 *  Created on: 28 Aug 2022
 *      Author: Dell
 */

#include"fifo.h"

error_state_t FIFO_INIT(FIFO_BUF_t* fifo,element_type* buf,int length)
{
	//if buffer point to null or not found...
	if(buf == NULL)
		return FIFO_NULL;

	//init fifo...
	fifo->length = length;
	fifo->count = 0;
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	return FIFO_NO_ERROR;
}

error_state_t FIFO_enqueue(FIFO_BUF_t* fifo,element_type item)
{
	//checking that base and head and tail point to thing not null.....
	if(!fifo->tail || !fifo->head || !fifo->base)
		return FIFO_NULL;

	//checking if fifo is full...
	if(FIFO_full(fifo) == FIFO_FULL)
		return FIFO_FULL;

	//else enqueue in the buffer...
	*(fifo->head) = item;
	fifo->count++;
	if(fifo->head == ((fifo->base) + (fifo->length * sizeof(element_type))))
		fifo->head = fifo->base;
	else
		fifo->head++;
	return FIFO_NO_ERROR;
}

error_state_t FIFO_dequeue(FIFO_BUF_t* fifo,element_type* item)
{
	//checking that base and head and tail point to thing not null.....
	if(!fifo->tail || !fifo->head || !fifo->base)
		return FIFO_NULL;

	//checking if fifo is full...
	if(FIFO_empty(fifo) == FIFO_EMPTY)
		return FIFO_EMPTY;

	//else dequeue from the buffer...
	*item = *(fifo->tail);
	fifo->count--;
	if(fifo->tail == ((fifo->base) + (fifo->length * sizeof(element_type))))
		fifo->tail = fifo->base;
	else
		fifo->tail++;
	return FIFO_NO_ERROR;
}

error_state_t FIFO_full(FIFO_BUF_t* fifo)
{
	if(fifo->count == fifo->length)
		return FIFO_FULL;
	return FIFO_NO_ERROR;
}

error_state_t FIFO_empty(FIFO_BUF_t* fifo)
{
	if(fifo->count == 0)
		return FIFO_EMPTY;
	return FIFO_NO_ERROR;
}

void print_FIFO(FIFO_BUF_t* fifo)
{
	element_type* temp;
	int i;
	if(fifo->count == 0)
		printf("FIFO is EMPTY.......\n");
	else
	{
		temp = fifo->tail;
		printf(".......fifo print................\n");
		for(i = 0;i < fifo->count;i++)
		{
			printf("<%d> \n",*temp);
			temp++;
		}
		printf("...........................................\n");
	}
}

