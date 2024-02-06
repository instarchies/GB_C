#include <stdio.h>
int Solution(int arr[5]){
    int min = arr[0];
    for(int i = 0; i < 5; i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}
int main(void){
    int arr[5];
    printf("Введите 5 чисел \n");
    for(int i = 0; i < 5; i++){
        scanf("%d", &arr[i]);
    }
    printf("%d \n", Solution(arr));
}