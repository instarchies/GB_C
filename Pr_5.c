#include <stdio.h>

int grains (int grain){
    int result = 1;
    if(grain < 0 || grain > 65){
        printf("Число должно быть больше 1 и меньше 64!");
    }
    for(int i = 1; i < grain; i++){
        result = result*2;

    }
    return result;
}

int nod(int a, int b){
    while(a > 0 && b > 0)
 
        if(a > b)
            a %= b;
 
        else
            b %= a;
    
    return a + b;
}

int is_happy_number(int n){
    int sum = 0;
        int proiz = 1;
        int n_sum = n;
        int n_proiz = n;
        int result;
    for(int i = 10; i < n; i++){
        
        while(n_sum != 0){
            sum += n_sum%10;
            n_sum /=10;
        }
        while(n_proiz != 0){
            proiz *= n_proiz%10;
            n_proiz /= 10;
        }
        if(sum == proiz) 
            return 0;
            
        else 
            return 1;
            
    }
}

int sum_of_series(int n){
    int sum = 0;
    for(int i = 1; i <= n; i++){
        sum += i;
    }
    return sum;
}




int main(void){
    
    printf("Задание №1 \n");
    int grain;
    scanf("%d", &grain);
    printf("%d \n", grains(grain));
    printf("Задание №2 \n");
    int a;
    int b;
    scanf("%d %d", &a, &b);
    printf("%d \n", nod(a,b));

    printf("Задание №3 \n");
    int n;
    scanf("%d", &n);
    is_happy_number(n);
    if(is_happy_number(n) == 0) {
        printf("YES \n");
        }
    else {
        printf("NO \n");
        }

    printf("Задание №4 \n");
    n = 0;
    scanf("%d", &n);
    printf("%d \n", sum_of_series(n));
}