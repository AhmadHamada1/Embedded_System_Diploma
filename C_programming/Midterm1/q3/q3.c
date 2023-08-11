/*
 * q3.c
 *
 *  Created on: 11 Aug 2023
 *      Author: Hamo
 */


/*c function to print all prime numbers between two numbers*/
#include<stdio.h>
void prime(int x,int y);
int main ()
{
	int x,y;
	printf("Enter two numbers to print prime between them :");
	fflush(stdout);
	scanf("%d%d",&x,&y);
	prime(x,y);
	return 0;
}
void prime(int x, int y)
{
	int i,j;
	printf("Prime numbers from %d to %d are:\n",x,y);
	fflush(stdout);
	for(i=x;i<=y;i++)
	{
		for(j=2;j<i;j++)
		{
			if((i%j) == 0)
				break;
			else
				continue;
		}
		if(j==i)
		{
			printf("%d\t",i);
			fflush(stdout);
		}
	}
}
