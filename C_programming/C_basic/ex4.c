#include "stdio.h"

int main()
{
	float num;
	printf("enter a number: ");
    fflush(stdout);
	scanf("%f", &num);
	if(num>0)
	{
		printf("%f is positive",num);
	}
	else if(num<0)
	{
		printf("%f is negative",num);
	}
	else
	{
		printf("you entered Zero");
	}
	return 0;
}
