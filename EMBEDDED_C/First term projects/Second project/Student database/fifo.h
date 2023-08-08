/*
 * fifo.h
 *
 *  Created on: 30 Oct 2022
 *      Author: aliab
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include"stdlib.h"
#include"string.h"
#include"math.h"

#define Dprintf(...) {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}




typedef struct{
	char Fname[50];
	char Lname[50];
	int roll;
	float gpa;
	int cid[5];
}Sstudent_t;

typedef struct{
	int count;
	int length;
	Sstudent_t *base;
	Sstudent_t *head;
	Sstudent_t *tail;
}fifo_buf_t;


void init(fifo_buf_t* fifo,Sstudent_t* buf, int length);
void add_student_from_file(fifo_buf_t* fifo);
void add_student_manually(fifo_buf_t* fifo);
void show_s(fifo_buf_t* fifo);
void find_rl(fifo_buf_t* fifo);
void up_s(fifo_buf_t* fifo);
void tot_s(fifo_buf_t* fifo);
void find_fn(fifo_buf_t* fifo);
void find_cid(fifo_buf_t* fifo);
#endif /* FIFO_H_ */
