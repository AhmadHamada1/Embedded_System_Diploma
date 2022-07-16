#include "stdio.h"

int main()
{
	char num;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &num);
	if((num >= 'A' && num <= 'Z')||(num >= 'a' && num <= 'z'))
	{
		printf("%c is an Alphabet", num);
	}
	else
	{
		printf("%c is not an Alphabet", num);
	}
	return 0;
}
