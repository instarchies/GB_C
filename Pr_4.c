#include <stdio.h>
#include <stdbool.h>

int Task1(int first, int second){
    int result = 0;
    for(int i = first; i <= second; i++){
        result += i * i;
    }
    return result;
}
void Task2(int number){
    int counter = 0;
    bool result;
    while (number)
    {
        number /=10;
        counter++;
    }
    if(counter == 3){
        printf("YES \n");
    }
    else if(counter != 3){
        printf("NO\n");
    }
}
void Task3(int number){
bool ifyes = false;
    for( ; number ;)
    {
        if(number % 2 == 0){
            ifyes = true;
        }
        else{
            ifyes = false;
            break;
        }
        number/=10;
    }
    if(ifyes == true){
        printf("YES \n");
    }
    else if(ifyes == false){
        printf("NO \n");
    }
}
int Task4(int number){
    int result = 0;
    while (number > 0) { 
        result = result * 10 + number % 10; 
        number  /= 10; 
    } 
    return result;
}

void Task5(int number){
    
    if(number< 10){
        printf("Число меньше 10!");
    }
    for(int i = 10; i<number;i++){
        int sum = 0;
        int proiz = 1;
        int ii = i;
        int iii = i;
        while(ii!=0){
            sum +=ii%10;
            ii /=10;
        }
        
        while(iii!=0){
            proiz *=iii%10;
            iii /=10;
        }
        if(sum == proiz){
            printf("%d ", i);
            
        }
        
    }
    
}

int main(void){

    printf("Введите первое число: \n");
    int first;
    scanf("%d", &first);
    printf("Введите второе число: \n");
    int second;
    scanf("%d", &second);

    printf("Результат суммы возведения чисел = %d \n", Task1(first, second));
    printf("\n");

    printf("Введите число: \n");
     int number;
    scanf("%d", &number);
    Task2(number);
    printf("\n");

    printf("Введите положительное число: \n");
    scanf("%d",&number);
    Task3(number);

    printf("\n");

    printf("Введите положительное число: \n");
    scanf("%d",&number);
    printf("Перевернутое число: %d \n",Task4(number));
    printf("\n");

    printf("Введите положительное натуральное число: \n");
    scanf("%d", &number);
    Task5(number);
    printf("\n");

}