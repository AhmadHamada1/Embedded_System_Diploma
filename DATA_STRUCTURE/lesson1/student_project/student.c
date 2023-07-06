/*
 * student.c
 *
 *  Created on: 29 Aug 2022
 *      Author: Dell
 */

#include"student.h"

Student_t* GPfristStudent = NULL;

error_state_t Add_student()
{
	Student_t* newStudent;
	Student_t* LastStudent;
	char temp[40];
	//checking if the list empty...
	if(!GPfristStudent)//the list is empty..
	{
		newStudent = (Student_t*)malloc(sizeof(Student_t));
		GPfristStudent = newStudent;
	}
	else//the list is not empty....
	{
		newStudent = (Student_t*)malloc(sizeof(Student_t));
		LastStudent = GPfristStudent;
		while(LastStudent->PNextStudent)
		{
			LastStudent = LastStudent->PNextStudent;
		}
		LastStudent->PNextStudent = newStudent;
	}
	//enter the student data....
	DPRINTF("enter the student id :");
	gets(temp);
	newStudent->student.id = atoi(temp);
	DPRINTF("enter the student name :");
	gets(newStudent->student.name);
	DPRINTF("enter the student height :");
	gets(temp);
	newStudent->student.height = atof(temp);
	//set the new student next to NULL......
	newStudent->PNextStudent = NULL;
	return S_NO_ERROR;
}

error_state_t Delete_student()
{
	char temp[40], selected_id;
	DPRINTF("enter the student id you want to delete :");
	gets(temp);
	selected_id = atoi(temp);
	if(GPfristStudent)
	{
		Student_t* selectedStudent = GPfristStudent;
		Student_t* prevStudent = NULL;
		while(selectedStudent)
		{
			if(selected_id == selectedStudent->student.id)
			{
				if(prevStudent)//1st student wasn't the selected to delete...
				{
					prevStudent->PNextStudent = selectedStudent->PNextStudent;
				}
				else//1st student that we want to delete...
				{
					GPfristStudent = selectedStudent->PNextStudent;
				}
				free(selectedStudent);
				return S_NO_ERROR;
			}
			prevStudent = selectedStudent;
			selectedStudent = selectedStudent->PNextStudent;
		}
		DPRINTF("the id isn't found...\n");
		return S_NOTFOUND;
	}
	else
	{
		DPRINTF("the list is empty....\n");
		return S_EMPTY;
	}
}

error_state_t DeleteAll_student()
{
	Student_t* currentStudent = GPfristStudent;
	if(!GPfristStudent)
	{
		DPRINTF("sorry..the list is already empty...!\n");
		return S_EMPTY;
	}
	else
	{
		while(currentStudent)
		{
			Student_t* temp = currentStudent;
			currentStudent = currentStudent->PNextStudent;
			free(temp);
		}
		DPRINTF("all student are deleted...\n");
		GPfristStudent = NULL;
		return S_NO_ERROR;
	}
}

void view_students()
{
	Student_t* Pdata = GPfristStudent;
	int count = 0;
	if(!GPfristStudent)
	{
		DPRINTF("the list is empty there is nothing to print...\n");
	}
	else
	{
		while(Pdata)
		{
			DPRINTF("================================\n");
			DPRINTF("==========the student record <%d> =============\n",count+1);
			DPRINTF("the student id is : %d\n",Pdata->student.id);
			DPRINTF("the student name is : %s\n",Pdata->student.name);
			DPRINTF("the student height is : %.2f\n",Pdata->student.height);
			Pdata = Pdata->PNextStudent;
			count++;
		}
		DPRINTF("the student data printed successfully...\n");
	}
}

error_state_t GetData_ofNthStudent()
{
	int count = 1,index;
	char index_text[10];
	Student_t* Pstudents = GPfristStudent;
	DPRINTF("enter the index of the element you want..... :");
	gets(index_text);
	index = atoi(index_text);
	while(Pstudents)
	{
		if(count == index)
		{
			DPRINTF("the student id of index <%d> is : %d\n",count,Pstudents->student.id);
			DPRINTF("the student name of index <%d> is : %s\n",count,Pstudents->student.name);
			DPRINTF("the student height of index <%d> is : %f\n",count,Pstudents->student.height);
			return S_NO_ERROR;
		}
		count++;
	}
	return S_NOTFOUND;
}

error_state_t GetNum_ofStudent()
{
	Student_t* Pstudent = GPfristStudent;
	int count = 0;
	if(!Pstudent->PNextStudent)
	{
		DPRINTF("the list is empty...\n");
		return S_NULL;
	}
	else
	{
		while(Pstudent)
		{
			Pstudent = Pstudent->PNextStudent;
			count++;
		}
		DPRINTF("the length of the list is :%d \n",count);
		return S_NO_ERROR;
	}
}

error_state_t GetData_ofNthStudentFromLast()
{
	Student_t* Pmain = GPfristStudent;
	Student_t* Pref = GPfristStudent;
	if(!Pmain)
	{
		DPRINTF("sorry..! the list is empty...\n");
		return S_NOTFOUND;
	}
	char temp[10];
	int num;
	DPRINTF("enter the number to Print n’th student from the end \n");
	gets(temp);
	num = atoi(temp);
	while(num>1)
	{
		Pref = Pref->PNextStudent;
		num--;
	}
	while(Pref)
	{
		Pmain = Pmain->PNextStudent;
		Pref = Pref->PNextStudent;
	}
	DPRINTF("the student id  is : %d\n",Pmain->student.id);
	DPRINTF("the student name is : %s\n",Pmain->student.name);
	DPRINTF("the student height is : %f\n",Pmain->student.height);
	return S_NO_ERROR;

}

error_state_t GetMiddle_ofStudentList()
{
	Student_t* Pslow = GPfristStudent;
	Student_t* Pfast = GPfristStudent;
	if(!Pslow)
	{
		DPRINTF("sorry..! the list is empty...\n");
		return S_NOTFOUND;
	}
	while(Pfast)
	{
		Pslow = Pslow->PNextStudent;
		Pfast = Pfast->PNextStudent->PNextStudent;
	}
	DPRINTF("==================the Middle student is ==========\n");
	DPRINTF("the Middle student id  is : %d\n",Pslow->student.id);
	DPRINTF("the Middle student name is : %s\n",Pslow->student.name);
	DPRINTF("the Middle student height is : %f\n",Pslow->student.height);
	return S_NO_ERROR;
}

error_state_t DetectLoop()
{
	Student_t* Pslow = GPfristStudent;
	Student_t* Pfast = GPfristStudent;
	if(!Pslow)
	{
		DPRINTF("sorry..! the list is empty...\n");
		return S_NOTFOUND;
	}
	while(Pslow && Pfast && Pfast->PNextStudent)
	{
		if(Pslow == Pfast)
		{
			DPRINTF("there is an infinite Loop...\n")
					return S_NULL;
		}
		Pslow = Pslow->PNextStudent;
		Pfast = Pfast->PNextStudent->PNextStudent;
	}
	DPRINTF("there isn't an infinite Loop...\n");
	return S_NO_ERROR;
}










