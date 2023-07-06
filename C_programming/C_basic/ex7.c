/*
 * ex7.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include <stdio.h>
int main ()
{
	int num, i, fact=1;
		printf("enter a number: ");
		fflush(stdin); fflush(stdout);
		scanf("%d", &num);
		if(num<0)
		{
			printf("Error!!! factorial of negative number doesn't exist");
		}
		else if (num ==0)
		{
			printf("factorial = 1");

		}
		else
		{
			for(i=1 ; i<=num ; i++)
			{
				fact *= i;
			}
			printf("factorial = %d", fact);
		}


}

