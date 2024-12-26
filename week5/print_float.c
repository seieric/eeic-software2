#include <stdio.h>

int main(void) {
    float f = 0.0000102411234;

    printf("%%f: %f\n", f);
    printf("%%.8f: %.8f\n", f);
    printf("%%e: %e\n", f);
    printf("%%.8e: %.8e\n", f);
    printf("%%a: %a\n", f);
    printf("%%.8a: %.8a\n", f);

    return 0;
}
