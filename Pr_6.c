#include <stdio.h>
#include <stdlib.h>
void print_num(int num){
    if(num == 0) return;
    int digit = num%10;
    print_num(num/10);
    printf("%d ", digit);
}
void forAtoB1(int num1, int num2){
    if(num1 < num2) return;
    printf("%d " , num1);
    forAtoB1(num1 - 1, num2);
}
void forAtoB2(int num1, int num2){
    if(num1 > num2) return;
    printf("%d " , num1);
    forAtoB2(num1 + 1, num2);
}
void all_odd(int mass[], int index){
    if(mass[index] == 0) return;
    if(mass[index] %2 !=0){
        printf("%d ", mass[index]);
    }
    all_odd(mass, index+1);
}
int recurs_power(int n, int p){
    if (p == 0) return 1;
    if (p % 2) return n * recurs_power(n, p - 1);
    int t = recurs_power(n, p / 2);
    return t * t;
}
int main(void){
    printf("Задание 1.\n");
    int num;
    scanf("%d", &num);
    print_num(num);
    printf("\n");

    printf("Задание 2.\n");
    printf("Введите два числа через Enter: \n");
    int num1;
    scanf("%d", &num1);
    int num2;
    scanf("%d", &num2);
    if(num1 > num2){
        forAtoB1(num1, num2);
    }
    if(num1 < num2){
        forAtoB2(num1, num2);
    }
    printf("\n");
    
    printf("Задание 4.\n");
    int mass[100];
    int input, index = 0;
    do {
        scanf("%d", &input);
        mass[index++] = input;
    } while (input != 0);
    all_odd(mass, 0);
    printf("\n");
    
    printf("Задание 6.\n");
    printf("Введите число: \n");
    int n;
    scanf("%d", &n);
    printf("Введите степень возведения: \n");
    int p;
    scanf("%d", &p);
    int result = recurs_power(n, p);
    printf("%d", result);
    printf("\n");
}
//Если можно, можете прислать решение 5 3 2 задания, интересно их выполнение ибо я не смог((