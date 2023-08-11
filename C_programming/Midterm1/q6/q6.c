/*
 * q6.c
 *
 *  Created on: 11 Aug 2023
 *      Author: Hamo
 */
/*c function to return unique number in array with one loop?*/
#include<stdio.h>
int main()
{
	int size;
	printf("Enter array size :\n");
	fflush(stdout);
	scanf("%d",&size);
	int arr[size],i,j;
	int freqArr[1000]={0};
	for(i=0;i<size;i++)
	{
		printf("Enter element no. %d: ",i);
		fflush(stdout);
		scanf("%d",&arr[i]);
		fflush(stdin);
		freqArr[arr[i]]++;
	}
	int res=0;
	for(j=0;j<100;j++)
	{
		if(freqArr[j]==1)
		{
			res=j;
			break;
		}
	}
	printf("%d",res);
	return 0;
}


