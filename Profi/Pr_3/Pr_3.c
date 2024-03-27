#include <stdio.h>

int main() {
    int N;
    long long int number, unique_number = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &number);
        unique_number ^= number;
    }
    printf("%lld\n", unique_number);
    return 0;
}
