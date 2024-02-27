#include <stdio.h>
#include <ctype.h>
void Solution(char *str){
    int i, j;
    int singleSpace = 0;
    int startOfLine = 1; // Флаг, указывающий на начало строки

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i]) || (isspace((unsigned char)str[i]) && !singleSpace)) {
            // Если текущий символ не пробел, или это пробел и предыдущий символ не был пробелом,
            // то сохраняем его
            if (startOfLine && !isspace((unsigned char)str[i])) { // Если начало строки и символ не пробел, снимаем флаг
                startOfLine = 0;
            }
            str[j++] = str[i];
            if (isspace((unsigned char)str[i])) {
                singleSpace = 1;
            } else {
                singleSpace = 0;
            }
        } else if (isspace((unsigned char)str[i])) {
            // Пропускаем оставшиеся пробелы до следующего непробельного символа
            while (isspace((unsigned char)str[i + 1])) {
                i++;
            }
        }
    }
    if (startOfLine) {
        str[j] = '\0'; // Если строка состоит только из пробелов, оставляем пустую строку
    } else {
        str[j] = '\0'; // Устанавливаем конец строки
    }
}