/*
 * q10.c
 *
 *  Created on: 11 Aug 2023
 *      Author: Hamo
 */
#include <stdio.h>

int MaxOnesBetweenZeros(int num) {
    int maxOnes = 0;
    int currentOnes = 0;
    int betweenZeros = 0;

    while (num > 0) {
        if (num & 1) {
            currentOnes++;
            if (betweenZeros > 0) {
                maxOnes = (currentOnes > maxOnes) ? currentOnes : maxOnes;
                currentOnes = 0;
            } else {
                maxOnes = (currentOnes > maxOnes) ? currentOnes : maxOnes;
            }

            betweenZeros = 1;
        }
        num >>= 1;  // Right-shift to consider the next bit
    }

    return maxOnes;
}

int main() {
    int num ;  // Binary: 1100101 (max ones between zeros: 2)
    printf("Enter The Number To find max num of ones between zeros: \n");
    	fflush(stdout);
    	scanf("%d",&num);
    int MaxOnes = MaxOnesBetweenZeros(num);



    printf("Max Ones Between Zeros: %d\n", MaxOnes);

    return 0;
}


