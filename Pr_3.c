#include <stdio.h>
#include <string.h>
int main(void){
    
    int arr[5];
    printf("Введите 5 чисел\n");
    for(int i = 0; i < 5; i++){
        scanf("%d", &arr[i]);
    }
    
    int max = arr[0];
    int min = arr[0];
    
    for(int i = 0; i<5; i++){
        if(arr[i]>max){
            max = arr[i];
        }

    }
    for(int i = 0; i<5;i++){
        if(arr[i]<min){
            min = arr[i];
        }
    }
    printf("Задание №1 \n");
    printf("Max = %d \n", max);
    printf("Задание №2 \n");
    printf("Min = %d \n", min);
    printf("Задание №3 \n");
    
    int arr1[5];
    printf("Введите 5 чисел\n");
    for(int i = 0; i < 5; i++){
        scanf("%d", &arr1[i]);
    }
    int one = arr1[0];
    char vozrast[4];
    for(int i = 0; i < 5; i++){
        if(arr1[i] > one){
            one = arr1[i];
            strcpy(vozrast, "Yes");
        }
        else{
            strcpy(vozrast, "No");
        }
    }
    printf("Ряд идет по порядку - %s \n", vozrast);
}