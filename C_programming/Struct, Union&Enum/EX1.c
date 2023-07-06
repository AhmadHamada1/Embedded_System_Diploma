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
	float marks;
}student;
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);setvbuf(stderr, NULL, _IONBF, 0);
	printf("enter information of student \n");
	printf("enter student name : ");
	gets(student.name);
	printf("enter student roll_num : ");
	scanf("%d",&student.roll_num);
	printf("enter student Marks : ");
	scanf("%f",&student.marks);
	printf("\n");
	printf("****Display information *****\n");
	printf("student name is : %s \n",student.name);
	printf("student roll_num : %d \n",student.roll_num);
	printf("student Marks : %f \n",student.marks);
	return 0;
}
