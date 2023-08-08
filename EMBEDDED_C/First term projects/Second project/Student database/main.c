/*
 * main.c
 *
 *  Created on: 30 Oct 2022
 *      Author: aliab
 */


#include "fifo.h"
int main(){
	char xx[10];
	fifo_buf_t fifo;
	Sstudent_t s[50];
	init(&fifo, s,50 );
	while(1){
		Dprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
		Dprintf("\t choose one of the following \n");
		Dprintf("1 Add student \n");
		Dprintf("2 View student \n");
		Dprintf("3 find student by roll number \n");
		Dprintf("4 update student \n");
		Dprintf("5 total number of students \n");
		Dprintf("6 find student by first name \n");
		Dprintf("7 View students enrolled in course id \n");
		Dprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
		gets(xx);
		switch(atoi(xx))
		{
		case 1:
			add_student_manually(&fifo);
			break;
		case 2:
			show_s(&fifo);
			break;
		case 3:
			find_rl(&fifo);
			break;
		case 4:
			up_s(&fifo);
			break;
		case 5:
			tot_s(&fifo);
			break;
		case 6:
			find_fn(&fifo);
			break;
		case 7:
			find_cid(&fifo);
			break;
		default:
			Dprintf("wrong option \n");
			break;
		}
	}
	return 0;
}
