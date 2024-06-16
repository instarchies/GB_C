#include <stdio.h>
#include <string.h>
#include "functions.h"

int main(void){
    char choice[20];
    char key[20];
    char _pers_acc[21];
    const char *filename = "clients_info.csv"; 
    printf("<add> Добавить нового клиента\n");
    printf("<show> Просмотреть список клиентов\n");
    printf("<find> Найти клиента\n");
    printf("<delete> Удаление клиента\n");
    printf("Выберите действие: ");
    scanf("%s", choice);
    if(strcmp(choice, "add") == 0){
        addNewClient();
    }
    else if(strcmp(choice, "show") == 0){
        printf("Введите ключ для расшифровки данных: ");
        scanf("%s", key);
        decryptClientToFile(filename, key);
    }
    else if(strcmp(choice, "find") == 0){
        printf("Введите ключ для расшифровки данных: ");
        scanf("%s", key);
        printf("Введите номер лицевого счета\n");
        scanf("%s", _pers_acc);
        searchClient(filename, key, _pers_acc);
    }
    else if(strcmp(choice, "delete") == 0){
        printf("Введите ключ для расшифровки данных: ");
        scanf("%s", key);
        printf("Введите номер лицевого счета\n");
        scanf("%s", _pers_acc);
        deleteClient(filename, key, _pers_acc);
    }
}
//реализация шифровки ++ 
//к каждой букве и цифре создаьб шифр ++ 
//в файл с данными записывать уже шифровку ++
//в отдельной функции реализовать алгоритм шифрования данных ++
//проверка на воод всех строк ++
//просьба ввода ключа для расшифровки ++
//поиск клиента по лицевому счету++
//удаление клиента по лицевому счету++
//подумать над тем, чтобы выводить пароль клиента не сразу
//подумать как спрятать ключ шифрования
//вывести инфу о созданном пользователе++
//пароль не больше 30 символов!
//при соханении подтвердить введенные данные++