#include <stdio.h>

int main(void){

    printf("Задание №1\n");
    int number1 = 4;
    int number2 = 5;
    int number3 = 7;
    int result1_1 = number1 + number2 + number3;
    printf("%d + %d + %d = %d \n", number1, number2, number3,result1_1);
    

    int number4 = 10;
    int number5 = 20;
    int number6 = 30;  
    int result1_2 = number4 + number5 + number6;
    printf("%d + %d + %d = %d \n", number4, number5, number6, result1_2);
    printf("\n");

    printf("Задание №2\n");
    int number7 = 1;
    int number8 = 2;
    int number9 = 3;
    int result2_1 = number7+number8+number9;
    int result2_2 = number7*number8*number9;
    printf("%d + %d + %d = %d \n", number7, number8, number9, result2_1);
    printf("%d * %d * %d = %d \n", number7, number8, number9, result2_2);

    number1 = 4;
    number2 = 5;
    number3 = 7;
    int result2_3 = number1 + number2 + number3;
    int result2_4 = number1 * number2 * number3;
    printf("%d + %d + %d = %d \n", number1, number2, number3,result2_3);
    printf("%d * %d * %d = %d \n", number1, number2, number3,result2_4);
    printf("\n");

    printf("Задание №3\n");
    number1 = 4;
    number2 = 5;
    int result3_1 = number1 - number2;
    printf("%d - %d = %d \n", number1, number2, result3_1);
    number3 = 100;
    number4 = 49;
    int result3_2 = number3 - number4;
    printf("%d - %d = %d \n", number3, number4, result3_2);
    printf("\n");

    printf("Задание №4\n");
    int n = 4351;
    double sum = 0;
    double result;
    for( ; n>0 ;){
        int nn = n%10;
        sum +=nn;
       
        n/=10;
    }
    result = sum/4;
    printf("Result = %.2f\n", result);

    n = 1020;
    sum = 0;
    result;
    for( ; n>0 ;){
        int nn = n%10;
        sum +=nn;
        n/=10;
    }
    result = sum/4;
    printf("Result = %.2f\n", result); //0.75
    //В методичке написано, мол ответ должен быть 1.50, но это если не учитывать, что 0 не есть цифра. 
    //Но если делать дз по заданию, то мы должны учитывать, что 0 это тоже цифра целого числа, поэтому после суммы должны делить на 4.
    //Если сделать так, чтобы ответ был как требуется, то код следующий:
    // for( ; n>0 ;){
    //     int nn = n%10;
    //     sum +=nn;
    //     n/=10;
    // }
    // result = sum/2;
    // printf("Result = %.2f\n", result); Ответ будет 1,5.
    return 0;
}