#include <stdio.h>
#include <string.h>

void reverseWords(char *str) {
    int length = strlen(str);
    int start = 0;

    for (int i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            for (int j = i - 1; j >= start; j--) {
                printf("%c", str[j]);
            }
            if (i < length) {
                printf(" ");
            }
            start = i + 1;
        }
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fflush(stdout);
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character

    printf("Original String: %s\n", str);

    printf("Reversed Words: ");
    reverseWords(str);

    return 0;
}
