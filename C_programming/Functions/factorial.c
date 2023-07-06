/*
 * main.c
 *
 *  Created on: Jul 31, 2022
 *      Author: madaa
 */
#include <stdio.h>
#include <stdlib.h>
int factorial(int n);
int main(){
	int n;
	printf("Enter an positive integer:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	printf("Factorial of %d = %d",n,factorial(n));


}
int factorial(int n)
{
	if(n!=1)
	{
		return n*factorial(n-1);
	}
}

