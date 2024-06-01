#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void removeOddIndices(char* input[], int n) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            input[j++] = input[i];
        }
    }
    input[j] = NULL;
}
int main() {
    char* input1[] = {"aa", "ss", "dd", "ff", "gg", "hh", "jj", "kk", "ll", NULL};
    char* input2[] = {"aa", "ss", "dd", "ff", "gg", "hh", "jj", "kk", "ll", "tt", NULL};
    int n1 = 0;
    while (input1[n1] != NULL) n1++;
    
    int n2 = 0;
    while (input2[n2] != NULL) n2++;
    removeOddIndices(input1, n1);
    removeOddIndices(input2, n2);
    printf("Результат первого ввода: ");
    for (int i = 0; input1[i] != NULL; i++) {
        printf("%s ", input1[i]);
    }
    printf("\n");
    printf("Результат второго ввода: ");
    for (int i = 0; input2[i] != NULL; i++) {
        printf("%s ", input2[i]);
    }
    printf("\n");
    return 0;
}
