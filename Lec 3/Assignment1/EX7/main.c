/*

 * main.c
 *
 *  Created on: Jul 6, 2022
 *      Author: madaa
 */
#include <Stdio.h>
void main()
{
	float a,b;
	printf("Enter a value of a: ");
	fflush(stdout);
	scanf("%f",&a);
	printf("Enter a value of b: ");
	fflush(stdout);
	scanf("%f",&b);
	a=a+b;
	b=a-b;
	a=a-b;

	printf("After swapping, value of a:%f \n ",a);
	printf("After swapping, value of b:%f \n",b);
}

