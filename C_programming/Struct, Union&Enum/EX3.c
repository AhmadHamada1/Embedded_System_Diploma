/*
 * main.c
 *
 *  Created on: 10 Feb 2022
 *      Author: Ahmed Hamada
 */
#include "stdio.h"

struct Number get_sum(struct Number num1,struct Number num2);

struct Number {
	float real;
	float imaginary;
}number1,number2,sum;

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);setvbuf(stderr, NULL, _IONBF, 0);
	printf("enter 1st Complex number : ");
	scanf("%f %f",&number1.real,&number1.imaginary);
	printf("enter 2nd Complex number : ");
	scanf("%f %f",&number2.real,&number2.imaginary);
	sum = get_sum(number1,number2);
	printf("sum = %f + (%f)j",sum.real,sum.imaginary);
	return 0;
}

struct Number get_sum(struct Number num1,struct Number num2)
{
	struct Number sum;
	sum.real = num1.real + num2.real;
	sum.imaginary = num1.imaginary + num2.imaginary;
	return sum;
}



