#include <stdio.h>
#include <stdbool.h>

void help(){
    printf("Статистика за месяц: \n");
        printf("-m <номер месяца> - Статистика за указанный месяц \n");
        printf("-sm <номер месяца> - Среднемесячная температура указанного месяца \n");
        printf("-maxm <номер месяца> - Максимальная температура указанного месяца \n");
        printf("-minm <номер месяца> - Минимальная температура за указанный месяц \n");
        printf("Статистика за год \n");
        printf("-sg - Среднегодовая температура \n");
        printf("-ys - Годовая статистика");
        printf("-maxg - Максимальная температура за год \n");
        printf("-ming - Минимальная температура за год \n");
}
void month_statistic(const char *filename, int _month) {
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    int line_number = 0;
    bool error_found = false;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
    }
    printf("YEAR   MONTH   DAY   HOUR   MINUTE   TEMPERATURE\n");
    while (!feof(file)) {
        line_number++;
        if (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) != 6) {
            error_found = true;
            while (fgetc(file) != '\n' && !feof(file));
            continue;
        }
        if(month == _month){
        printf("%-6d %-7d %-6d %-7d %-8d %-10.2f\n", year, month, day, hour, minute, temperature);
        }
    }
    fclose(file);
}
void month_arithmetic_mean(const char *filename, int _month){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    int month_counter = 0;
    float month_temperature_sum = 0.0;
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Ошибка чтения файла!");
    }
    while (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) == 6) {
        if(month == _month){
            month_counter++;
            month_temperature_sum += temperature;
        }
    }
    printf("Средняя температура по месяцам:\n"); 
    if (month_counter > 0) {
        float average_temperature = month_temperature_sum / month_counter;
        printf("Месяц %d: %.2f\n", _month, average_temperature);
    } else {
        printf("Месяц %d: данные отсутствуют\n", _month);
    }
    fclose(file);
}

void min_t(const char *filename, int _month){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    bool found = false;
    float min_tmp;
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Ошибка чтения файла");
    }
    while (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) == 6) {
        if(month == _month){
            if(!found || temperature < min_tmp){
                min_tmp = temperature;
                found = true;
            }
        }
    }
    fclose(file);
    if(found){
        printf("Минимальная температура для %d месяца: %.2f\n",_month, min_tmp);
    }
}

void max_t(const char *filename, int _month){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    bool found = false;
    float max_tmp;
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Ошибка чтения файла");
    }
    while (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) == 6) {
        if(month == _month){
            if(!found || temperature > max_tmp){
                max_tmp = temperature;
                found = true;
            }
        }
    }
    fclose(file);
    if(found){
        printf("Максимальная температура для %d месяца: %.2f\n",_month, max_tmp);
    }
}

void vivod(const char *filename){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    int line_number = 0;
    bool error_found = false;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
    }
    printf("YEAR   MONTH   DAY   HOUR   MINUTE   TEMPERATURE\n");
    while (!feof(file)) {
        line_number++;
        if (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) != 6) {
            printf("Ошибка: Некорректный формат данных в строке %d. Пропуск строки.\n", line_number);
            error_found = true;
            while (fgetc(file) != '\n' && !feof(file));
            continue;
        }
        printf("%-6d %-7d %-6d %-7d %-8d %-10.2f\n", year, month, day, hour, minute, temperature);
    }
    fclose(file);
}

void year_a_m(const char *filename){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    int year_counter = 0;
    float year_temperature_sum = 0.0;
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Ошибка чтения файла!");
    }
    while (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) == 6) {
        year_counter++;
        year_temperature_sum += temperature;
    }
    printf("Средняя температура по месяцам:\n"); 
    if (year_counter > 0) {
        float average_temperature = year_temperature_sum / year_counter;
        printf("Среднегодовая температура: %.2f\n", average_temperature);
    } else {
        printf("Данные отсутствуют \n");
    }
    fclose(file);
}
void max_g(const char *filename){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    bool found = false;
    float max_tmp;
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Ошибка чтения файла");
    }
    while (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) == 6) {
        if(!found || temperature > max_tmp){
            max_tmp = temperature;
            found = true;
        }
    }
    fclose(file);
    if(found){
        printf("Максимальная температура за год: %.2f\n", max_tmp);
    }
}
void min_g(const char *filename){
    FILE *file;
    int year, month, day, hour, minute;
    float temperature;
    bool found = false;
    float min_tmp;
    file = fopen(filename, "r");
    if(file == NULL){
        printf("Ошибка чтения файла");
    }
    while (fscanf(file, "%d;%d;%d;%d;%d;%f", &year, &month, &day, &hour, &minute, &temperature) == 6) {
       
        if(!found || temperature < min_tmp){
            min_tmp = temperature;
            found = true;
        }
    }
    fclose(file);
    if(found){
        printf("Максимальная температура за год: %.2f\n", min_tmp);
    }
}