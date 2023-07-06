/*
 * main.c
 *
 *  Created on: Jul 27, 2022
 *      Author: madaa
 */
#include <stdio.h>
int main(){
	printf("Enter the number of data:");
	fflush(stdin); fflush(stdout);

	int n,i;
	scanf("%d", &n);
	float num[n];
	float sum =0;
	for(i=0;i<n;i++){
        printf("enter the number");
    	fflush(stdin); fflush(stdout);

        scanf("%f",&num[i]);
        sum=sum+num[i];
    }
	fflush(stdin); fflush(stdout);

    printf("Average= %f\n",sum/n);


    return 0;
}




