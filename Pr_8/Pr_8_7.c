#include <stdio.h>
void color_of_chess(char arr[]){
    int n = (int)(arr[1]);
    if(arr[0] == 'A' || arr[0] == 'C' || arr[0] == 'E' || arr[0] == 'G'){
        if(n % 2 == 0 ){printf("White \n");}
        else{printf("Black \n");}
    }
    else if(arr[0] == 'B' || arr[0] == 'D' || arr[0] == 'F' || arr[0] == 'H'){
        if(n % 2 != 0){printf("White \n");}
        else{printf("Black \n");}
    }
}
int main(void){
    char a[] = "G7";
    color_of_chess(a);
}