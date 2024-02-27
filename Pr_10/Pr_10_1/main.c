#include <stdio.h>
#include "solution.h"
#define MAX_LENGTH 1000
int main(void){
    FILE *inputfile;
    const char *filename = "txt_1";
    char word[MAX_LENGTH];
    inputfile = fopen("txt_1", "r");
    if (inputfile == NULL) {
        perror("Unable to open the file");
        return 1;
    }
    fgets(word, sizeof(word), inputfile);
    fclose(inputfile);
    printf("%s\n", word);
    Solution(word);
    FILE *newfile;
    const char *newfilename = "new.txt";
    newfile = fopen(newfilename, "w");
    if(newfile == NULL){
        printf("Не удалось создать файл для записи \n");
        return 0;
    }
    fprintf(newfile, "%s", word);
    
    printf("Строка%s успешно записана\n", word);
    return 0;
}
