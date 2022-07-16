/*

 * ex3.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include "stdio.h"


int main()
{
	float num1, num2, num3;
	printf("Enter 3 numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&num1, &num2, &num3);
	if(num1>num2&&num1>num3)
		printf("largest number is: %f",num1);
	else if (num2>num1&&num2>num3)
		printf("largest number is: %f",num2);
	else
		printf("largest number is: %f",num3);
	return 0;
}

