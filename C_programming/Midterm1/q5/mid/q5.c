#include <stdio.h>

int countBinary(unsigned int num) {
    int count = 0;

    while (num > 0) {
        if (num & 1) {
            count++;
        }
        num >>= 1;  // Right-shift to consider the next bit
    }

    return count;
}

int main() {
	int num;
	printf("Enter a number to get number of ones in it's binary representation: \n");
	fflush(stdout);
		scanf("%d",&num);
    int onesCount = countBinary(num);

    printf("Number of Ones in Binary: %d\n", onesCount);

    return 0;
}
