#include <stdio.h>
void Solution(int arr[]){
    int frequency[10] = {0}; 
    for (int i = 0; i < 10; i++) {
        frequency[arr[i]]++;
    }
    int maxFrequency = 0;
    int mostFrequentNumber = arr[0];
    for (int i = 0; i < 10; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            mostFrequentNumber = i;
        }
    }
    printf("%d \n", mostFrequentNumber);
}
int main(void){
    int arr[10];
    printf("Введите 10 чисел");
    for(int i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
    }
    Solution(arr);
}