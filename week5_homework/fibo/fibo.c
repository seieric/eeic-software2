#include "fibo.h"

#include <assert.h>
#include <stdio.h>

struct mat2x2 {
    long a, b, c, d;
};

long fibo(const int n) {
    assert(0 <= n && n <= 90);

    if (n == 0) return 0;
    if (n == 1) return 1;

    Mat2x2 a = mat_a(n - 1);
    return a.a;
}

Mat2x2 mat_a(const int n) {
    if (n == 1) return (Mat2x2){.a = 1, .b = 1, .c = 1, .d = 0};

    if (n % 2 == 0) {
        Mat2x2 x = mat_a(n / 2);
        return mat_mul(x, x);
    } else {
        Mat2x2 x = mat_a((n - 1) / 2);
        return mat_mul(mat_mul(x, x), (Mat2x2){.a = 1, .b = 1, .c = 1, .d = 0});
    }
}

Mat2x2 mat_mul(const Mat2x2 x, const Mat2x2 y) {
    return (Mat2x2){.a = x.a * y.a + x.b * y.c,
                    .b = x.a * y.b + x.b * y.d,
                    .c = x.c * y.a + x.d * y.c,
                    .d = x.c * y.b + x.d * y.d};
}