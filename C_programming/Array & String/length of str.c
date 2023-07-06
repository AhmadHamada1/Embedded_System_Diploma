/*
 * main.c
 *
 *  Created on: Jul 27, 2022
 *      Author: madaa
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

	char str[100];
	int i,count=0;
	printf("enter the string\n");
	fflush(stdin); fflush(stdout);
	fgets(str,sizeof(str),stdin);
	for(i=0;str[i]!='\0';i++){
		if(str[i]==' '){
			continue;
		}
		count++;
	}
	printf(" the count = %d \n",count-1);

	return 0;
}

