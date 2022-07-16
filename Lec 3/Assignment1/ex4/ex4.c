/*
 * ex4.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include <stdio.h>

void main()
{
	float a,b;
	printf("enter two integers: ");
	fflush(stdout);
	scanf("%f %f", &a, &b);
	printf("product: %f", a*b);
	return 0;
}

