#include <stdio.h>

#include "fibo.h"

int main(void) {
    for (int i = 0; i <= 90; i++) {
        printf("fibo(%d) = %ld\n", i, fibo(i));
    }
    return 0;
}