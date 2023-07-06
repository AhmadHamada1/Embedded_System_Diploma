/*
 * Lifo.h
 *
 *  Created on: 27 Aug 2022
 *      Author: Dell
 */

#ifndef LIFO_H_
#define LIFO_H_

#include"stdio.h"
#include"stdlib.h"
//type definitions

typedef struct {
	unsigned int length;
	unsigned int count;
	unsigned int* base;
	unsigned int* head;
}LIFO_BUF_t;

//error states
typedef enum{
	LIFO_NO_ERROR,
	LIFO_FULL,
	LIFO_EMPTY,
	LIFO_NULL
}LIFO_STATE_t;

//APIs
LIFO_STATE_t LIFO_INIT(LIFO_BUF_t* lifo_buf,unsigned int* buf,unsigned int length);
LIFO_STATE_t LIFO_ADD_item(LIFO_BUF_t* lifo_buf,unsigned int item);
LIFO_STATE_t LIFO_GET_item(LIFO_BUF_t* lifo_buf,unsigned int* item);

#endif /* LIFO_H_ */
