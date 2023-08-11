/*
 * q8.c
 *
 *  Created on: 11 Aug 2023
 *      Author: Hamo
 */
/*c function to take an array and reverse its elements?*/
#include<stdio.h>
void reverse (int arr[],int size);
int main()
{
	int size;
	printf("Enter size of array of integers: \n");
	fflush(stdout);
	scanf("%d",&size);
	int arr[size],i;
	for(i=0;i<size;i++)
	{
		scanf("%d",&arr[i]);
	}
	reverse(arr,size);
	printf("After reversing: \n");
	fflush(stdout);
	for(i=0;i<size;i++)
	{
		printf("%d\t",arr[i]);
	}
}
void reverse (int arr[],int size)
{
	int i,temp,tempsize=size;

	for(i=0;i<size/2;i++)
	{
		temp=arr[i];
		arr[i]=arr[tempsize-1];
		arr[tempsize-1]=temp;
		tempsize--;
	}
}


