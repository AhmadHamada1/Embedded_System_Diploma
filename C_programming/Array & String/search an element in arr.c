#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	int siz,i,desired_num,arr[10];
	printf("enter the number of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&siz);

	printf("enter %d element\n",siz);
	fflush(stdin); fflush(stdout);
	for(i=0;i<siz;i++){
		scanf("%d",&arr[i]);
	}

	printf("enter the desired number: ");
	fflush(stdin);
    fflush(stdout);
	scanf("%d",&desired_num);

	i=0;
			while(i<siz&&desired_num!=arr[i])
			{
				i++;
			}
			if(i<siz)
			{
				printf("number found at the location=%d",i+1);
			}
			else
				printf("number not found");
return 0  ;

}


