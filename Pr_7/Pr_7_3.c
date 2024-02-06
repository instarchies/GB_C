#include <stdio.h>
void Solution(int arr[12]){
    int temp[12];
    int startIndex = (12 -4)%12;
    for(int i = 0; i < 12; i++){
        temp[i] = arr[(startIndex + i) % 12];
    }
    for(int i = 0; i < 12; i++){
        arr[i] = temp[i];
        printf("%d ", arr[i]);
    }
}
int main(void){
    int arr[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    Solution(arr);
}