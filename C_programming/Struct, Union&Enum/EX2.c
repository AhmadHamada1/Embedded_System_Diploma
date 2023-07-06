/*
 * main.c
 *
 *  Created on: 10 Feb 2022
 *      Author: Ahmed Hamada
 */
#include "stdio.h"

struct Distance {
	int feet;
	float inches;
}distance1,distance2,sum;
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);setvbuf(stderr, NULL, _IONBF, 0);
	printf("enter information of 1st Distance \n");
	printf("enter feet : ");
	scanf("%d",&distance1.feet);
	printf("enter inches : ");
	scanf("%f",&distance1.inches);
	printf("enter information of 2nd Distance \n");
	printf("enter feet : ");
	scanf("%d",&distance2.feet);
	printf("enter inches : ");
	scanf("%f",&distance2.inches);
	sum.feet = distance1.feet + distance2.feet;
	sum.inches = distance1.inches + distance2.inches;
	/*every 12 inche = 1 feet.*/
	while(sum.inches >= 12)
	{
		sum.inches -= 12;
		sum.feet++;
	}
	printf("sum of Distance = %d\' -%f\" ",sum.feet,sum.inches);
	return 0;
}


