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

    char string[100], character;
    int i,count=0;

    printf("enter the string\n");
	fflush(stdin); fflush(stdout);
    //fgets(string, sizeof(string),stdin);   //way to scan from array "string array"
	gets(string);
    printf("enter the char\n");
	fflush(stdin); fflush(stdout);
    scanf("%c",&character);
    for(i=0; string[i] != '\0';i++){
        if(character == string[i]){
            count+=1;
        }
    }
    printf("the frequency of char %c = %d\n",character,count);

    return 0;
}


