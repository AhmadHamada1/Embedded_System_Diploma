/*
 * main.c
 *
 *  Created on: 10 Feb 2022
 *      Author: Ahmed Hamada
 */

#include "stdio.h"

struct Student {
	char name[20];
	int roll_num;
	int marks;
};
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);setvbuf(stderr, NULL, _IONBF, 0);
	int i;
	struct Student students[10];
	printf("****enter information of students****** \n");
	for(i = 0;i < 10;i++)
	{
		printf("for roll number (%d) \n",i+1);
		printf("enter student name : ");
		gets(students[i].name);
		printf("enter student Marks : ");
		scanf("%d",&students[i].marks);
	}
	printf("****Display information *****\n");
	for(i = 0;i < 10;i++)
	{
		printf("for roll number (%d) \n",i+1);
		printf("student name is : %s \n",students[i].name);
		printf("student Marks : %d \n",students[i].marks);
	}

	return 0;
}


