#include <stdio.h>
void Solution(int arr[4]){
    double result = 0;
    double sum = 0;
    for(int i = 0; i < 5; i++){
        sum += arr[i];
    }
    result = sum/5;
    printf("%.3f \n", result);
}
int main(void){
    int arr[4];
    printf("Введите 5 ненулевых числа \n");
    for(int i = 0; i < 5; i++){
        scanf("%d", &arr[i]);
    }
    Solution(arr);
}