#include <stdbool.h>
int is_two_same(int size, int a[]){
    bool isTwoSame = false;
    for(int i = 0; i < size - 1; i++){
        for(int j = i+1; j < size;j++){
            if(a[i] == a[j]){
                isTwoSame = true;
            }
        }
    }
    if(isTwoSame){ return 1; }
    else{ return 0; }
}
