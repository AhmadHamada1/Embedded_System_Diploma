#include <stdio.h>

unsigned int reverseDigits(unsigned int num) {
    unsigned int reversed = 0;

    while (num > 0) {
        unsigned int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }

    return reversed;
}

int main() {
     int num;
     printf("Enter number to reverse: \n");
         fflush(stdout);
         	scanf("%d",&num);
     int reversedNum = reverseDigits(num);


    printf("Reversed Number: %u\n", reversedNum);

    return 0;
}
