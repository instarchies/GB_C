#include<stdio.h>
#include<string.h>
#define MAX_LENGTH 100
void Solution(char *word, const char *filename, int size){
    FILE *file = fopen("txt_2", "w"); 
    if (file == NULL) {
        perror("Unable to open the file");
        return;
    }
    for(int i = 0; word[i] != '\0'; i++){
        if(word[i] == 'a')
        {
            word[i] = 'b';
        }
        else if(word[i] == 'A'){
            word[i] = 'B';
        }
        else if(word[i] == 'b'){
            word[i] = 'a';
        }
        else if(word[i] == 'B'){
            word[i] = 'A';
        }
        printf("%c", word[i]);
        
        fprintf(file, "%c", word[i]);
    }
    printf("Файл txt_2 перезаписан.");
    fclose(file);
}
int main(void){
    FILE *inputfile;
    const char *filename = "txt_2.txt";
    char word[MAX_LENGTH];
    inputfile = fopen("txt_2", "r");
    if (inputfile == NULL) {
        perror("Unable to open the file");
        return 1;
    }
    fscanf(inputfile, "%s", word);
    fclose(inputfile);
    size_t size = sizeof(word);
    Solution(word, filename, size);
    printf("\n");
}