#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    int a[10][10], trans[10][10],r,c,i,j;
    printf("enter rows and columns \n");
	fflush(stdin); fflush(stdout);
    scanf("%d%d",&r,&c);
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("enter the element\n");
        	fflush(stdin); fflush(stdout);
            scanf("%d",&a[i][j]);
        }
    }

    printf("the array is \n");
   	fflush(stdin); fflush(stdout);
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d\t",a[i][j]);
            if (j==c-1){
                printf("\n");
            }
        }
    }

    printf("the transpose is \n");
   	fflush(stdin); fflush(stdout);
    printf("\n");
    for(i=0;i<c;i++){
        for(j=0;j<r;j++){
            printf("%d\t",a[j][i]);
            if (j==r-1){
                printf("\n");
            }
        }
    }




    return 0;
}
