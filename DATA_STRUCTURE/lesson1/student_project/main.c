/*
 * main.c
 *
 *  Created on: 29 Aug 2022
 *      Author: Dell
 */

#include"student.h"

int main()
{
	char temp[10];
	while(1)
	{
		DPRINTF("\n =======================");
		DPRINTF("\n\t Choose one from the following options ");
		DPRINTF("\n 1: Add student ");
		DPRINTF("\n 2: Delete student");
		DPRINTF("\n 3: View all students");
		DPRINTF("\n 4: Delete all students");
		DPRINTF("\n 5: get the index'th student data ");
		DPRINTF("\n 6: get number of student  ");
		DPRINTF("\n 7: get n’th student from the Last");
		DPRINTF("\n 8: get the middle student in the List");
		DPRINTF("\n 9: to Detect if there is infinite loop");
		DPRINTF("\n Enter option number :");
		gets(temp);
		DPRINTF("===============================\n");
		switch(atoi(temp))
		{
		case 1:
			Add_student();
			break;
		case 2:
			Delete_student();
			break;
		case 3:
			view_students();
			break;
		case 4:
			DeleteAll_student();
			break;
		case 5:
			GetData_ofNthStudent();
			break;
		case 6:
			GetNum_ofStudent();
			break;
		case 7:
			GetData_ofNthStudentFromLast();
			break;
		case 8:
			GetMiddle_ofStudentList();
			break;
		case 9:
			DetectLoop();
			break;
		default:
			DPRINTF("wrong option...\n");
			break;
		}
	}
	return 0;
}
