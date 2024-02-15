#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1000
int Solution(const char *str){
    char word[100];
    int c = 0;
    int i = 0;
    for(int j = 0; str[j] != '\0'; j++){
        char ch = str[j];
        if(isalpha(ch) || isdigit(ch)){
            word[i++] = ch;
        }
        else if(i > 0){
            word[i] = '\0';
            if(word[i-1] == 'a'){
                c++;
            }
            i = 0;
        }
    }
    return c;
}

int main(void){
    FILE *inputFile, *outputFile;
    char line[MAX_LENGTH];
    int numbers[MAX_LENGTH];
    int count = 0;
    inputFile = fopen("txt_6", "r");
    if (inputFile == NULL) {
        perror("Unable to open the input file");
        return 1;
    }
    fgets(line, sizeof(line), inputFile);
    fclose(inputFile);
    int result = Solution(line);
    printf("%d ", result);
    printf("\n");
    inputFile = fopen("txt_6", "a");
    if (inputFile == NULL) {
        perror("Unable to open the file");
        return 1;
    }
    fprintf(inputFile, "\nКоличество слов, в которых последння буква 'a': %d\n", result);
    printf("Данные записались в файл txt_6");
    fclose(inputFile);
    return 0;
}