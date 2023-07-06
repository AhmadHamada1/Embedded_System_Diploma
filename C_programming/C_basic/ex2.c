/*
 * ex2.c
 *
 *  Created on: Jul 7, 2022
 *      Author: madaa
 */
#include "stdio.h"

void main()
{
	char c;
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &c);
	if(c == 'a' ||c == 'A' ||c == 'e' ||c == 'E' ||c == 'I' ||c == 'i' ||c == 'O' ||c == 'o' ||c == 'u' ||c == 'U')
	{
		printf("%c is a vowel\n", c);
	}
	else
	{
		printf("%c is consonant\n", c);
	}
	return 0;
}

