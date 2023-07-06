/*
 * fifo.h
 *
 *  Created on: 28 Aug 2022
 *      Author: Dell
 */

#ifndef FIFO_H_
#define FIFO_H_

#include"stdio.h"
#include"stdlib.h"

//choose any element type you want (char , int(default), float, ........).
#define element_type int
//choose the width of the buffer you want...
#define width 5

//fifo type definition
typedef struct {
	int length;
	int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_BUF_t;

//error states
typedef enum {
	FIFO_NO_ERROR,
	FIFO_NULL,
	FIFO_FULL,
	FIFO_EMPTY
}error_state_t;

//APIs
error_state_t FIFO_INIT(FIFO_BUF_t* fifo,element_type* buf,int length);
error_state_t FIFO_enqueue(FIFO_BUF_t* fifo,element_type item);
error_state_t FIFO_dequeue(FIFO_BUF_t* fifo,element_type* item);
error_state_t FIFO_empty(FIFO_BUF_t* fifo);
error_state_t FIFO_full(FIFO_BUF_t* fifo);
void print_FIFO(FIFO_BUF_t* fifo);


#endif /* FIFO_H_ */
