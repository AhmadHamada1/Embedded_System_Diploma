/*
 * main.c
 *
 *  Created on: 27 Aug 2022
 *      Author: Dell
 */
#include"LIFO.h"

unsigned int buffer1[5];


int main()
{
	unsigned int i,temp = 0,state = 0;
	LIFO_BUF_t UART,I2C;
	LIFO_INIT(&UART,buffer1,5);
	unsigned int* buffer2 = (unsigned int*)malloc(5 * sizeof(unsigned int));//dynamic allocation 5*4 = 20.
	LIFO_INIT(&I2C,buffer2,5);
	printf("static allocation buffer (add item)...\n");
	printf("==============================\n");
	for(i = 1;i < 7;i++)
	{
		state = LIFO_ADD_item(&UART,i);
		if(state == LIFO_FULL)
			printf("LIFO is FULL...\n");
		if(state == LIFO_NULL)
			printf("LIFO isnot found---->NULLL...\n");
		if(state == LIFO_NO_ERROR)
			printf("item-> (%d) ADD to LIFO BUFFER \n",i);
	}
	printf("=======================================\n");
	printf("static allocation buffer (add item)...\n");
	printf("=============================\n");
	for(i = 1;i < 7;i++)
	{
		state = LIFO_ADD_item(&I2C,i);
		if(state == LIFO_FULL)
			printf("LIFO is FULL...\n");
		if(state == LIFO_NULL)
			printf("LIFO isnot found---->NULLL...\n");
		if(state == LIFO_NO_ERROR)
			printf("item-> (%d) ADD to LIFO BUFFER \n",i);
	}
	printf("=======================================\n");
	printf("static allocation buffer (getting item)...\n");
	printf("=============================\n");
	for(i = 1;i < 7;i++)
	{
		state = LIFO_GET_item(&UART,&temp);
		if(state == LIFO_EMPTY)
			printf("LIFO is EMPTY...\n");
		if(state == LIFO_NULL)
			printf("LIFO isnot found---->NULLL...\n");
		if(state == LIFO_NO_ERROR)
			printf("item-> (%d) getting from LIFO BUFFER \n",i);
	}
	printf("=======================================\n");
	printf("static allocation buffer (getting item)...\n");
	printf("=============================\n");
	for(i = 1;i < 7;i++)
	{
		state = LIFO_GET_item(&I2C,&temp);
		if(state == LIFO_EMPTY)
			printf("LIFO is EMPTY...\n");
		if(state == LIFO_NULL)
			printf("LIFO isnot found---->NULLL...\n");
		if(state == LIFO_NO_ERROR)
			printf("item-> (%d) getting from LIFO BUFFER \n",i);
	}
	return 0;
}
