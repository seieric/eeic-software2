#include <stdio.h>

int main(void) {
    char text[4 * sizeof(float)] = "Hello,World\n";

    for (int i = 0; i < 4; ++i)
        printf("f[%d] = %.8a;\n", i, ((float *)text)[i]);

    char text2[4 * sizeof(float)] = "hello,World\n";
    printf("f[0] += %.8a;\n", ((float *)text2)[0] - ((float *)text)[0]);

    return 0;
}