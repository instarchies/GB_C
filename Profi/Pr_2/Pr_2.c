#include <stdio.h>
#include <stdint.h> 

int main() {
    uint32_t N32;
    uint64_t N64;
    uint64_t mask32 = UINT64_C(0xFFFFFFFF);
    uint64_t mask64 = UINT64_C(0xFFFFFFFF00000000);
    int input_success = 0; 
    printf("Введите число: ");
    if (scanf("%u", &N32) == 1) { 
        N32 ^= mask32;
        printf("Результат: %u\n", N32);
        input_success = 1;
    } 
    else if (scanf("%lu", &N64) == 1) { 
        N64 ^= mask64;
        printf("Результат: %lu\n", N64);
        input_success = 1;
    } 
    if (!input_success) {
        printf("Ошибка ввода.\n");
    }
    
    return 0;
}
