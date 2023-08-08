/*
 * fifo.c
 *
 *  Created on: 30 Oct 2022
 *      Author: aliab
 */

#include "fifo.h"
char temp[50];
int i,x,j,k;
Sstudent_t* temp_pointer;
// Initiate the fifo
void init(fifo_buf_t* fifo,Sstudent_t* buf, int length){
	fifo->count = 0;
	fifo->length = length;
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	Dprintf("============= fifo initialised ===============\n")
}





void add_student_manually(fifo_buf_t* fifo){
	Dprintf("Enter student roll number : \n");
	gets(temp);

	temp_pointer = fifo->base;


	for(i=0; i<fifo->count ; i++){
		if(atoi(temp) == temp_pointer->roll){
			break;
		}else{
			temp_pointer++;
		}
	}

	if(i < fifo->count){

		Dprintf("roll id is already existed");

	}else{
		(fifo->count)++;
		(fifo->head->roll) = atoi(temp);

		Dprintf("Enter student first name : \n");
		gets(fifo->head->Fname);


		Dprintf("Enter student last name : \n");
		gets(fifo->head->Lname);


		Dprintf("Enter student gpa : \n");
		gets(temp);

		(fifo->head->gpa) = atof(temp);

		for (i = 0; i < 5 ; i++){
			Dprintf("Enter course id  : \n");
			scanf("%d",&x);

				fifo->head->cid[i] = x;


		}

		if(fifo->head == fifo->base + (sizeof(Sstudent_t) * fifo->length))
			fifo->head = fifo->base;
		else
			fifo->head++;
	}
}

void show_s(fifo_buf_t* fifo){
	temp_pointer = fifo->base;
	for(i = 0; i < fifo->count;i++){
		Dprintf("==========================student %d====================\n",i+1);
		Dprintf("student first name :%s\n" ,temp_pointer->Fname);
		Dprintf("student last name :%s\n",temp_pointer->Lname);
		Dprintf("student roll number :%d\n",temp_pointer->roll);
		Dprintf("student GPA :%f\n",temp_pointer->gpa);
		for (j = 0; j < 5 ; j++){
			if(temp_pointer->cid[j] == 0)
				break;

			Dprintf("course %d\n",temp_pointer->cid[j]);
		}
		temp_pointer++;
		Dprintf("======================================================== \n");
	}
}





void find_rl(fifo_buf_t* fifo){

	Dprintf("Enter student roll number : \n");
	gets(temp);

	temp_pointer = fifo->base;


	for(i=0; i<fifo->count ; i++){
		if(atoi(temp) == temp_pointer->roll){
			break;
		}else{
			temp_pointer++;
		}
	}
	if(i < fifo->count){

		Dprintf("student first name :%s\n" ,temp_pointer->Fname);
		Dprintf("student last name :%s\n",temp_pointer->Lname);
		Dprintf("student roll number :%d\n",temp_pointer->roll);
		Dprintf("student GPA :%f\n",temp_pointer->gpa);
		for (j = 0; j < 5 ; j++){
			if(temp_pointer->cid[j] == 0)
				break;

			Dprintf("course %d\n",temp_pointer->cid[j]);
		}

		Dprintf("======================================================== \n");

	}else{
		Dprintf("this student does not existed \n");
	}


}
void up_s(fifo_buf_t* fifo){

	Dprintf("Enter student roll number : \n");
	gets(temp);

	temp_pointer = fifo->base;


	for(i=0; i<fifo->count ; i++){
		if(atoi(temp) == temp_pointer->roll){
			break;
		}else{
			temp_pointer++;
		}
	}
	if(i < fifo->count){

		Dprintf("Enter student first name : \n");
		gets(temp_pointer->Fname);


		Dprintf("Enter student last name : \n");
		gets(temp_pointer->Lname);


		Dprintf("Enter student gpa : \n");
		gets(temp);

		(temp_pointer->gpa) = atof(temp);


		for (i = 0; i < 5 ; i++){
			temp_pointer->cid[i] = 0;
		}
		for (i = 0; i < 5 ; i++){
			Dprintf("Enter course id : \n");
			scanf("%d",&x);

				temp_pointer->cid[i] = x;


		}


		Dprintf("======================================================== \n");

	}else{
		Dprintf("this student does not existed \n");
	}


}

void tot_s(fifo_buf_t* fifo){

	Dprintf("total numbers of students is %d \n",fifo->count);
}



void find_fn(fifo_buf_t* fifo){

	Dprintf("Enter student name : \n");
	gets(temp);
	//	Dprintf("%s",temp);

	temp_pointer = fifo->base;


	for(i=0; i<fifo->count ; i++){
		if(!strcmp(temp,temp_pointer->Fname)){
			Dprintf("==========================student %d====================\n",i+1);
			Dprintf("student first name :%s\n" ,temp_pointer->Fname);
			Dprintf("student last name :%s\n",temp_pointer->Lname);
			Dprintf("student roll number :%d\n",temp_pointer->roll);
			Dprintf("student GPA :%f\n",temp_pointer->gpa);
			for (j = 0; j < 5 ; j++){
				if(temp_pointer->cid[j] == 0)
					break;

				Dprintf("course %d\n",temp_pointer->cid[j]);
			}
		}

		temp_pointer++;

	}

}


void find_cid(fifo_buf_t* fifo){

	Dprintf("Enter Course ID : \n");
	gets(temp);
	x=atoi(temp);

	//	Dprintf("%s",temp);

	temp_pointer = fifo->base;


	for(i=0; i<fifo->count ; i++){
		for(j=0; j<5;j++){
			if(x == temp_pointer->cid[j]){
				Dprintf("==========================student %d====================\n",i+1);
				Dprintf("student first name :%s\n" ,temp_pointer->Fname);
				Dprintf("student last name :%s\n",temp_pointer->Lname);
				Dprintf("student roll number :%d\n",temp_pointer->roll);
				Dprintf("student GPA :%f\n",temp_pointer->gpa);
				for (k = 0; k < 5 ; k++){
					if(temp_pointer->cid[k] == 0)
						break;

					Dprintf("course %d\n",temp_pointer->cid[k]);
				}
			}
		}

		temp_pointer++;

	}


}
