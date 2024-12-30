#include <stdio.h>

int main(void) {
    float f[4];

    // 以下に適切な値を設定する
    f[0] = 0x1.d8ca9000p+89;
    f[1] = 0x1.ae58de00p+95;
    f[2] = 0x1.c8d8e400p-107;
    f[3] = 0x0.00000000p+0;

    // "Hello,World\n" と出力してほしい
    printf("%s", (char*)f);

    // f[0] をいじる
    f[0] += 0x1.00000000p+71;
    // "hello,World\n" と出力してほしい
    printf("%s", (char*)f);

    return 0;
}
