#include <stdio.h>
#include <stdint.h>
int main(void){
    int n, k;
    int max = 0;
    int count = 0;
    printf("Введите, сколько хотите ввести чисел: %d \n", k);
    scanf("%d", &k);
    printf("Теперь вводите цифры\n");
    for(int i = 0; i < k; i++){
        scanf("%d", &n);
        if(n > max){
            max = n;
            count = 1;
        }
        else if (n == max){
            count++;
        }
    }
    printf("Всего максимальных чисел: %d\n", count);
}