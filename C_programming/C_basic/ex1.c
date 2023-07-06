/*
 * ex1.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include "stdio.h"

int main()
{
	int num;
	printf("Enter an integer you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	if(num%2 == 0)
	{
		printf("%d is even\n", num);
	}
	else
	{
		printf("%d is odd\n", num);
	}
	return 0;
}

