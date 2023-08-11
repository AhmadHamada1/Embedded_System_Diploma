/*
 * q7.c
 *
 *  Created on: 11 Aug 2023
 *      Author: Hamo
 */
/*c function to sum numbers from 1 to 100*/
#include<stdio.h>
void sum();
int main()
{
	sum();
	return 0;
}
void sum()
{
	static int result=0;
	static int i=1;
	result+=i;
	i++;
	if(i>100)
		printf("%d",result);
	else
		sum();
}


