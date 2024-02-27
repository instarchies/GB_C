#include <stdio.h>
#include "solution.h"
#define MAX_LENGTH 1000
int main(void){
    char filename[100];
    printf("Введите имя файла (.txt): ");
    scanf("%s", filename);

    Solution(filename);
}