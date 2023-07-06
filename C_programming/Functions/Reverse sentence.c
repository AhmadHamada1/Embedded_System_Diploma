/*
 * main.c
 *
 *  Created on: Jul 31, 2022
 *      Author: madaa
 */
#include <stdio.h>
void rev();
int main() {
	printf("Enter a sentence: ");
	fflush(stdin);fflush(stdout);
	rev();
	return 0;

}
void rev()
{
	char c;
	scanf("%c",&c);
	if(c!='\n')
	{
		rev();
		printf("%c",c);
	}
}

