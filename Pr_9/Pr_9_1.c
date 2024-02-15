#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100
void findUniqueChars(const char *word1, const char *word2) {
    int freq1[256] = {0};
    int freq2[256] = {0};
    int i;
    for (i = 0; word1[i] != '\0'; i++)
        freq1[(int)word1[i]]++;
    for (i = 0; word2[i] != '\0'; i++)
        freq2[(int)word2[i]]++;
    printf("Characters that occur exactly once in both words:\n");
    for (i = 0; i < 256; i++) {
        if (freq1[i] == 1 && freq2[i] == 1) {
            printf("%c ", (char)i);
        }
    }
    printf("\n");
}

int main() {
    FILE *file;
    char word1[MAX_LENGTH], word2[MAX_LENGTH];
    file = fopen("txt_1", "r");
    if (file == NULL) {
        perror("Unable to open the file");
        return 1;
    }
    fscanf(file, "%s %s", word1, word2);
    fclose(file);
    findUniqueChars(word1, word2);
    return 0;
}
