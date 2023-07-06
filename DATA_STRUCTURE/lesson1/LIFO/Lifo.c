/*
 * Lifo.c
 *
 *  Created on: 27 Aug 2022
 *      Author: Dell
 */
#include"LIFO.h"

LIFO_STATE_t LIFO_INIT(LIFO_BUF_t* lifo_buf,unsigned int* buf,unsigned int length)
{
	//if the array not found in dynamic allocation(the heap is full).
	if(buf == NULL)
		return LIFO_NULL;
	lifo_buf->length = length;
	lifo_buf->count  = 0;
	lifo_buf->base   = buf;
	lifo_buf->head   = buf;
	return LIFO_NO_ERROR;
}

LIFO_STATE_t LIFO_ADD_item(LIFO_BUF_t* lifo_buf,unsigned int item)
{
	//if the lifo is not found or init.
	if(!lifo_buf->base || !lifo_buf->head)
		return LIFO_NULL;

	//if the lifo is full
	if(lifo_buf->count == lifo_buf->length)
		return LIFO_FULL;

	//if the lifo is valid and not full-----> ADD item.
	*(lifo_buf->head) = item;
	lifo_buf->head++;
	lifo_buf->count++;
	return LIFO_NO_ERROR;
}

LIFO_STATE_t LIFO_GET_item(LIFO_BUF_t* lifo_buf,unsigned int* item)
{
	//if the lifo is not found or init.
	if(!lifo_buf->base || !lifo_buf->head)
		return LIFO_NULL;

	//if the lifo is empty
	if(lifo_buf->count == 0)
		return LIFO_EMPTY;

	//if the lifo is valid and not empty-----> get item.
	lifo_buf->head--;
	*item = *(lifo_buf->head);
	lifo_buf->count--;
	return LIFO_NO_ERROR;
}
