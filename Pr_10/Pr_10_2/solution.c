#include <stdio.h>
#include <string.h>
void Solution(const char *filename){
    FILE *inputFile, *outputFile;
    char newFileName[100];

    // Открытие файла для чтения
    inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    // Изменение расширения файла на ".html"
    strcpy(newFileName, filename);
    char *dot = strrchr(newFileName, '.'); // Находим последнюю точку в имени файла
    if (dot != NULL) {
        strcpy(dot, ".html"); // Заменяем расширение на ".html"
    } else {
        strcat(newFileName, ".html"); // Если точка не найдена, просто добавляем ".html" в конец имени файла
    }

    // Открытие файла для записи
    outputFile = fopen(newFileName, "w");
    if (outputFile == NULL) {
        printf("Не удалось создать файл для записи.\n");
        fclose(inputFile);
        return;
    }

    // Копирование содержимого из одного файла в другой
    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile);
    }

    printf("Готово. Результат записан в файл %s.\n", newFileName);

    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);
}