#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int arr[20],element,location,num;
	printf("enter the number of elements \n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);

	//insert the array
	int i;
	printf("enter %d elements in array\n",num);
	fflush(stdin); fflush(stdout);
	for(i=0;i<num;i++){
		scanf("%d",&arr[i]);
	}
	printf("Enter the element want to insert:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&element);
	printf("Enter the location:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);

	for(int i=num ; i>=location;i--){
		arr[i]=arr[i-1];
	}
	num++;
	arr[location-1]=element;
	printf("new array : \t");
	for(i=0;i<=num;i++){
		printf("%d\t",arr[i]);
	}



	return 0;


}
