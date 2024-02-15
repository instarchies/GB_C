#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 1000
int Solution(const char *str, int *numbers){
    int c = 0;
    const char *ptr = str;
    while(*ptr != '\0'){
        if(isdigit(*ptr)){
            numbers[c++] = atoi(ptr);
            while(isdigit(*ptr)){
                ptr++;
            }
        }
        else{
            ptr++;
        }
    }
    return c;
}

int main(void){
    FILE *inputFile, *outputFile;
    char line[MAX_LENGTH];
    int numbers[MAX_LENGTH];
    int count = 0;
    inputFile = fopen("txt_3", "r");
    if (inputFile == NULL) {
        perror("Unable to open the input file");
        return 1;
    }
    fgets(line, sizeof(line), inputFile);
    fclose(inputFile);
    int c = Solution(line, numbers);
    for(int i = 0; i < c; i++){
        for(int j = i + 1; j < c; j++){
            if(numbers[i] > numbers[j]){
                int _arr = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = _arr;
            }
        }
        printf("%d ", numbers[i]);
        
    }
    printf("\n");
    inputFile = fopen("txt_3", "a");
    if (inputFile == NULL) {
        perror("Unable to open the file");
        return 1;
    }
    for(int i = 0; i < c; i++){
        fprintf(inputFile, "\n %d", numbers[i]);
    }
    printf("Данные записались в файл txt_3 \n");
    fclose(inputFile);
    return 0;
}