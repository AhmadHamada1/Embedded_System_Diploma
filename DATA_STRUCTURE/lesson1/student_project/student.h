/*
 * student.h
 *
 *  Created on: 29 Aug 2022
 *      Author: Dell
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include"stdio.h"
#include"stdlib.h"
#include "string.h"
#include "conio.h"

#define DPRINTF(...)   {fflush(stdout);\
						fflush(stdin);\
						printf(__VA_ARGS__);\
						fflush(stdout);\
						fflush(stdin);}
//data definition
typedef struct S_data{
	int id;
	char name[40];
	float height;
}S_DATA_t;

//dynamic data definition
typedef struct Student{
	S_DATA_t student;
	struct Student* PNextStudent;
}Student_t;

//error states
typedef enum {
	S_NO_ERROR,
	S_NULL,
	S_NOTFOUND,
	S_EMPTY
}error_state_t;

//APIs
error_state_t Add_student();
error_state_t Delete_student();
error_state_t DeleteAll_student();
void view_students();
error_state_t GetData_ofNthStudent();
error_state_t GetNum_ofStudent();
error_state_t GetData_ofNthStudentFromLast();
error_state_t GetMiddle_ofStudentList();
error_state_t DetectLoop();

#endif /* STUDENT_H_ */
