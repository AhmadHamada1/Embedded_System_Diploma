/*
 * ex8.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include <stdio.h>
int main()
{
	float num1,num2,result;
	char op;
	printf("enter an operator (+,-,*,/): ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &op);

	printf("enter 2 operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &num1, &num2);
	if(op=='+'){
		result=num1+num2;
		printf("%.1f %c %.1f = %.1f", num1, op, num2, result);
	}
	else if(op=='-'){
		result=num1-num2;
		printf("%.1f %c %.1f = %.1f", num1, op, num2, result);

	}
	else if(op=='*'){
		result=num1*num2;
		printf("%.1f %c %.1f = %.1f", num1, op, num2, result);

	}
	else if (op=='/'){
		if(num2 == 0)
		{
			printf("division by 0 is not possible!!!\n");
		}
		else
		{
			result = num1 / num2;
			printf("%.1f %c %.1f = %.1f", num1, op, num2, result);
		}

	}
	return 0;

}

