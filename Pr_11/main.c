#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"

int main(void){
    char filename[30];
    char str[20]; 
    int month_number;
    printf("Введите файл, с котором хотите работать: ");
    scanf("%s", filename);
    while (getchar() != '\n');
    printf("Введите команду: ");
    fgets(str, sizeof(str), stdin); 
    if (strncmp(str, "-h", 2) == 0) {
        help();
    } 
    else if (strncmp(str, "-sm", 3) == 0 && sscanf(str + 3, "%d", &month_number) == 1) {
        month_arithmetic_mean(filename, month_number);
    } 
    else if (strncmp(str, "-maxm", 5) == 0 && sscanf(str + 5, "%d", &month_number) == 1) {
        max_t(filename, month_number);
    } 
    else if (strncmp(str, "-minm", 5) == 0 && sscanf(str + 5, "%d", &month_number) == 1) {
        min_t(filename, month_number);
    } 
    else if (strncmp(str, "-sg", 3) == 0) {
        year_a_m(filename);
    } 
    else if (strncmp(str, "-maxg", 5) == 0){
        max_g(filename);
    } 
    else if (strncmp(str, "-ming", 5) == 0) {
        min_g(filename);
    } 
    else if (strncmp(str, "-ys", 3) == 0) {
        statistic(filename);
    } 
    else if (strncmp(str, "-m", 2) == 0 && sscanf(str + 2, "%d", &month_number) == 1) {
        month_statistic(filename, month_number);
    } 
    else {
        printf("Неправильный формат строки.\n");
    }
    return 0;
}