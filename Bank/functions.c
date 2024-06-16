#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#define MAX_CLIENTS 1000000
typedef struct {
    char surname[50];
    char name[50];
    char partonimic[50];
    int day;
    int month;
    int year;
    
    char pers_acc[21];
    char password[20];
    char num_pasport[10];
} Client;
int intEncr(int num){
   return num * 98;
}
int intYearEncr(int num){
    return num * 25;
}
int intDecr(int num){
    return num /98;
}
int intYearDecr(int num){
    return num /25;
}
void caseEncrNum(char *str){
    int i = 0;
    while (str[i] != '\0') {
        if ((str[i] >= 'A' && str[i] <= 'Z')) {
            str[i] = 'A' + (str[i] - 'A' + 6) % 26;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'a' + (str[i] - 'a' + 6) % 26;
        } else if (str[i] >= '0' && str[i] <= '9') {
            str[i] = '0' + (str[i] - '0' + 6) % 10;
        } else {

        }
        i++;
    }
}
void caseEncr(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if ((unsigned char)str[i] >= 0xC0 && (unsigned char)str[i] <= 0xDF) {
            str[i] += 6;
            str[i+1] += 6;
            i += 2;
        }
        else {
            i++;
        }
    }
}
void encryption(Client *client, const char *filename){
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }
    caseEncr(client->surname);
    caseEncr(client->name);
    caseEncr(client->partonimic);
    client->day = intEncr(client->day);
    client->month = intEncr(client->month);
    client->year = intYearEncr(client->year);
    caseEncrNum(client->num_pasport);
    caseEncrNum(client->pers_acc);
    caseEncrNum(client->password);
    fprintf(file, "%s;%s;%s;%d;%d;%d;%s;%s;%s\n",
            client->surname, client->name, client->partonimic, client->day, client->month, client->year, client->num_pasport, client->pers_acc, client->password);
    fclose(file);
}
void caseDecrNum(char *str){
    int i = 0;
    while (str[i] != '\0') {
        if ((str[i] >= 'A' && str[i] <= 'Z')) {
            str[i] = 'Z' - ('Z' - str[i] + 6) % 26;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'z' - ('z' - str[i] + 6) % 26;
        } else if (str[i] >= '0' && str[i] <= '9') {
            str[i] = '9' - ('9' - str[i] + 6) % 10;
        } else {
            
        }i++;
    }
}
void caseDecr(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if ((unsigned char)str[i] >= 0xC0 && (unsigned char)str[i] <= 0xDF) {
            str[i] -= 6;
            str[i+1] -= 6;
            i += 2;
        } else {
            i++;
        }
    }
}

Client* decrypt(const char *filename, char key[20], int* numClients){
    static Client decryptedData[MAX_CLIENTS]; // Статический массив структур
    *numClients = 0; // Инициализируем количество клиентов
    
    bool boolkey = false;
    char realkey[20] = "gbciot";
    if(strcmp(key, realkey) == 0){
        boolkey = true;
    }
    else{
        boolkey = false;
    }
    if(boolkey == true){
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return NULL;
        }
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            // Проверяем, не превысили ли максимальное количество клиентов
            if (*numClients >= MAX_CLIENTS) {
                printf("Превышено максимальное количество клиентов.\n");
                break;
            }
            // Читаем данные и дешифруем их
            sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%10[^;];%20[^;];%20[^\n]", 
                    decryptedData[*numClients].surname, decryptedData[*numClients].name, decryptedData[*numClients].partonimic, 
                    &decryptedData[*numClients].day, &decryptedData[*numClients].month, &decryptedData[*numClients].year, 
                    decryptedData[*numClients].num_pasport, decryptedData[*numClients].pers_acc, decryptedData[*numClients].password);
            caseDecr(decryptedData[*numClients].surname);
            caseDecr(decryptedData[*numClients].name);
            caseDecr(decryptedData[*numClients].partonimic);
            decryptedData[*numClients].day = intDecr(decryptedData[*numClients].day);
            decryptedData[*numClients].month = intDecr(decryptedData[*numClients].month);
            decryptedData[*numClients].year = intYearDecr(decryptedData[*numClients].year);
            caseDecrNum(decryptedData[*numClients].num_pasport);
            caseDecrNum(decryptedData[*numClients].pers_acc);
            caseDecrNum(decryptedData[*numClients].password);
            (*numClients)++; // Увеличиваем количество клиентов
        }
        fclose(file);
    }
    else{
        printf("Ввели неправильный ключ \n");
    }
    return decryptedData;
}
void decryptClientToFile(const char *filename, char key[20]) {
    bool boolkey = false;
    char realkey[20] = "gbciot";
    if(strcmp(key, realkey) == 0){
        boolkey = true;
    }
    else{
        boolkey = false;
    }
    if(boolkey == true){
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return;
        }
        char line[256];
        printf("Данные о клиентах: \n");
        printf("------------------------------------- \n");
        while (fgets(line, sizeof(line), file)) {
            char surname[50], name[50], partonimic[50], num_pasport[10], pers_acc[21], password[20];
            int day, month, year;
            if (sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%10[^;];%20[^;];%20[^\n]", 
                    surname, name, partonimic, &day, &month, &year, num_pasport, pers_acc, password) == 9) {
                caseDecr(surname);
                caseDecr(name);
                caseDecr(partonimic);
                day = intDecr(day);
                month = intDecr(month);
                year = intYearDecr(year);
                caseDecrNum(num_pasport);
                caseDecrNum(pers_acc);
                caseDecrNum(password);
                printf("Фамилия: %s \nИмя: %s \nОтчество: %s \nДата рождения: %d.%d.%d \nНомер паспорта: %s \nЛицевой счет: %s\nПароль: %s \n", surname, name, partonimic, day, month, year, num_pasport, pers_acc, password);
                printf("------------------------------------- \n");
            }
        }
        fclose(file);
    }
    else{
        printf("Ввели неправильный ключ \n");
    }
}
void random_pers_acc(char *str){
    srand(time(NULL)); 
    for (int i = 0; i < 20; ++i) {
        str[i] = '0' + rand() % 10;
    }
    str[20] = '\0';
}

void searchClient(const char *filename, char key[20], char _pers_acc[20]){
    bool boolkey = false;
    char realkey[20] = "gbciot";
    if(strcmp(key, realkey) == 0){
        boolkey = true;
    }
    else{
        boolkey = false;
    }
    if(boolkey == true){
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return;
        }
        char line[256];
        printf("Данные о клиентах: \n");
        while (fgets(line, sizeof(line), file)) {
            char surname[50], name[50], partonimic[50], num_pasport[10], pers_acc[21], password[20];
            int day, month, year;
            if (sscanf(line, "%49[^;];%49[^;];%49[^;];%d;%d;%d;%10[^;];%20[^;];%20[^\n]", 
                    surname, name, partonimic, &day, &month, &year, num_pasport, pers_acc, password) == 9) {
                caseDecr(surname);
                caseDecr(name);
                caseDecr(partonimic);
                day = intDecr(day);
                month = intDecr(month);
                year = intDecr(year);
                caseDecrNum(pers_acc);
                caseDecrNum(password);
                if(strcmp(pers_acc, _pers_acc) == 0){
                    printf("------------------------------------- \n");
                    printf("Фамилия: %s \nИмя: %s \nОтчество: %s \nДата рождения: %d.%d.%d \nНомер паспорта: %s \nЛицевой счет: %s\nПароль: %s \n", surname, name, partonimic, day, month, year, num_pasport, pers_acc, password);
                    printf("------------------------------------- \n");
                }
                
            }
        }
        fclose(file);
    }
    else{
        printf("Ввели неправильный ключ \n");
    }
}
void addNewClient(){
    Client client;
    const char *filename = "clients_info.csv";
    bool txt = false;
    
    while(txt == false){
        
        printf("Введите Фамилию: ");
        scanf("%s", client.surname);
        for(int i = 0; i < strlen(client.surname);i++){
            if(client.surname[i] >= '0' && client.surname[i] <= '9'){
                printf("Ошибка ввода! \n");
                memset(client.surname, 0, sizeof(client.surname));
                txt = false;
                break;
            }
            else{
                txt = true;
            }
        }
    }
    txt = false;
    while(txt == false){
        printf("Введите Имя: ");
        scanf("%s", client.name);
        for(int i = 0; i < strlen(client.name);i++){
            if(client.name[i] >= '0' && client.name[i] <= '9'){
                printf("Ошибка ввода! \n");
                memset(client.name, 0, sizeof(client.name));
                txt = false;
                break;
            }
            else{
                txt = true;
            }
        }
    }
    txt = false;
    while(txt == false){
        printf("Введите Отчество: ");
        scanf("%s", client.partonimic);
        for(int i = 0; i < strlen(client.partonimic);i++){
            if(client.partonimic[i] >= '0' && client.partonimic[i] <= '9'){
                printf("Ошибка ввода!\n");
                memset(client.partonimic, 0, sizeof(client.partonimic));
                txt = false;
                break;
            }
            else{
                txt = true;
            }
        }
    
    }
    char input[20];
    while (1) {
        printf("Введите День рождения: ");
        scanf("%s", input);
        int i = 0;
        while (input[i]) {
            if (!isdigit(input[i])) {
                printf("Введите число!\n");
                break;
            }
            i++;
        }
        if (input[i] == '\0') {
            client.day = atoi(input);
            break;
        }
    }
    memset(input, 0 , strlen(input));
    while (1) {
        printf("Введите месяц рождения: ");
        scanf("%s", input);
        int i = 0;
        while (input[i]) {
            if (!isdigit(input[i])) {
                printf("Введите число!\n");
                break;
            }
            i++;
        }
        if (input[i] == '\0') { 
            client.month = atoi(input);
            break;
        }
    }
    memset(input, 0 , strlen(input));
    while (1) {
        printf("Введите год рождения: ");
        scanf("%s", input);
        int i = 0;
        while (input[i]) {
            if (!isdigit(input[i])) {
                printf("Введите число!\n");
                break;
            }
            i++;
        }
        if (input[i] == '\0') { 
            client.year = atoi(input);
            break;
        }
    }
    
    txt = false;
    while (txt == false)
    {
        printf("Введите Пароль: ");
        scanf("%s", client.password);
        if(strlen(client.password) < 8){
            printf("Пароль должен быть больше 8 символов! \n");
            txt = false; 
            
            memset(client.password, 0, strlen(client.password));
        }
        else{
            txt = true;
        }
    }
    txt = false;
    while (txt == false)
    {
        printf("Введите номер паспорта: ");
        scanf("%s", client.num_pasport);
        if(strlen(client.num_pasport) < 10 || strlen(client.num_pasport) > 10){
            printf("Количество символов должно быть 10! \n");
            txt = false; 
            
            memset(client.num_pasport, 0, strlen(client.num_pasport));
            
        }
        else{
            txt = true;
            
        }
    }
    random_pers_acc(client.pers_acc);
    // printf("------------------------------------- \n");
    // printf("Фамилия: %s \nИмя: %s \nОтчество: %s \nДата рождения: %d.%d.%d \nНомер паспорта: %s \nЛицевой счет: %s\nПароль: %s \n", client.surname, client.name, client.partonimic, client.day, client.month, client.year, client.num_pasport, client.pers_acc, client.password);
    // printf("------------------------------------- \n");
    // encryption(&client, filename);
    char confirm;
    do {
        printf("\nДанные введены верно? (y/n): ");
        scanf(" %c", &confirm);
        if (confirm == 'y' || confirm == 'Y') {
            printf("\nДанные сохранены.\n");
            printf("-------------------------------------\n");
            printf("Фамилия: %s\nИмя: %s\nОтчество: %s\nДата рождения: %d.%d.%d\nНомер паспорта: %s\nЛицевой счет: %s\nПароль: %s\n", client.surname, client.name, client.partonimic, client.day, client.month, client.year, client.num_pasport, client.pers_acc, client.password);
            printf("-------------------------------------\n");
            encryption(&client, filename);
            return;
        } else if (confirm == 'n' || confirm == 'N') {
            // Начать заново
            addNewClient();
            return;
        } else {
            printf("Неверный ввод. Попробуйте еще раз.\n");
        }
    } while (1);
}

void encryptionToFile(Client *client, const char *filename){
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    // Шифруем данные перед записью в файл
    caseEncr(client->surname);
    caseEncr(client->name);
    caseEncr(client->partonimic);
    client->day = intEncr(client->day);
    client->month = intEncr(client->month);
    client->year = intYearEncr(client->year);
    caseEncrNum(client->num_pasport);
    caseEncrNum(client->pers_acc);
    caseEncrNum(client->password);

    // Записываем зашифрованные данные в файл
    fprintf(file, "%s;%s;%s;%d;%d;%d;%s;%s;%s\n",
            client->surname, client->name, client->partonimic, client->day, client->month, client->year, client->num_pasport, client->pers_acc, client->password);
    fclose(file);
}

void deleteClient(const char *filename, char key[20], char _pers_acc[20]) {
    int numClients;
    Client* decryptedData = decrypt(filename, key, &numClients);
    
    if(decryptedData == NULL) {
        printf("Ошибка при дешифровке данных.\n");
        return;
    }

    bool boolkey = false;
    char realkey[20] = "gbciot";
    if(strcmp(key, realkey) == 0){
        boolkey = true;
    }
    else{
        boolkey = false;
    }
    if(boolkey == true){
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return;
        }
        char line[256];
        char tempFileName[] = "temp.csv";
        FILE *tempFile = fopen(tempFileName, "w");
        if (tempFile == NULL) {
            printf("Ошибка создания временного файла.\n");
            fclose(file);
            return;
        }
        bool found = false;
        for(int i = 0; i < numClients; i++) {
            if(strcmp(_pers_acc, decryptedData[i].pers_acc) == 0){
                found = true;
            } else {
                // Используем функцию encryptionToFile для сохранения зашифрованных данных
                Client client;
                strcpy(client.surname, decryptedData[i].surname);
                strcpy(client.name, decryptedData[i].name);
                strcpy(client.partonimic, decryptedData[i].partonimic);
                client.day = decryptedData[i].day;
                client.month = decryptedData[i].month;
                client.year = decryptedData[i].year;
                strcpy(client.num_pasport, decryptedData[i].num_pasport);
                strcpy(client.pers_acc, decryptedData[i].pers_acc);
                strcpy(client.password, decryptedData[i].password);
                encryptionToFile(&client, tempFileName);
            }
        }
        fclose(file);
        fclose(tempFile);
        remove(filename);
        rename(tempFileName, filename);
        if (found) {
            printf("Клиент с лицевым счетом %s удален.\n", _pers_acc);
        } else {
            printf("Клиент с лицевым счетом %s не найден.\n", _pers_acc);
        }
    }
    else{
        printf("Ввели неправильный ключ \n");
    }
    // Освобождаем память после использования
    
}




