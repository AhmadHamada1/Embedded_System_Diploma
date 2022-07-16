/*
 * ex6.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include <stdio.h>
int main()
{
	int num  , i , sum=0;
	printf("inter an integer:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&num);
	for(i=1 ; i<=num ; i++)
	{
		sum+=i;
	}
	printf("sum= %d",sum);
	return 0;


}

