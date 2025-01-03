#include "matrix.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

struct mat {
    int height;
    int width;
    double *array;
};

Mat *mat_mul(Mat *a, Mat *b) {
    assert(a->width == b->height);
    const int h = a->height;
    const int w = b->width;

    Mat *mat = mat_create(h, w);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            double sum = 0;
            for (int k = 0; k < a->width; ++k) {
                sum += a->array[i * a->width + k] * b->array[j + k * w];
            }
            mat->array[i * w + j] = sum;
        }
    }
    return mat;
}

Mat *mat_dot(Mat *a, Mat *b) {
    assert((a->height == b->height && a->width == b->width) ||
           (a->height == b->width && a->width == b->height));
    const int n = a->height * a->width;

    Mat *mat = mat_create(a->height, a->width);
    if (a->height == b->height) {
        for (int i = 0; i < n; ++i) {
            mat->array[i] = a->array[i] * b->array[i];
        }
        return mat;
    } else {
        for (int i = 0; i < n; ++i) {
            mat->array[i] =
                a->array[i] * b->array[i / b->height + i % b->height];
        }
        return mat;
    }
}

Mat *mat_times_x(Mat *a, double x) {
    const int n = a->height * a->width;

    Mat *mat = mat_create(a->height, a->width);
    for (int i = 0; i < n; ++i) {
        mat->array[i] = a->array[i] * x;
    }
    return mat;
}

void mat_minus_inplace(Mat *a, Mat *b) {
    assert(a->height == b->height && a->width == b->width);
    const int n = a->height * a->width;
    for (int i = 0; i < n; ++i) {
        a->array[i] = a->array[i] - b->array[i];
    }
}

Mat *mat_create(const int height, const int width) {
    Mat *mat = (Mat *)malloc(sizeof(Mat));
    double *array = (double *)malloc(height * width * sizeof(double));
    *mat = (Mat){.height = height, .width = width, .array = array};
    return mat;
}

void mat_destroy(Mat *a) {
    free(a->array);
    free(a);
}

void mat_print(Mat *a) {
    for (int i = 0; i < a->height; ++i) {
        printf("[");
        for (int j = 0; j < a->width; ++j) {
            printf("%lf ", a->array[i * a->width + j]);
        }
        printf("]\n");
    }
}

void mat_he_init(Mat *a) {
    const int n = a->height * a->width;
    const double stddev = sqrt(2.0 / a->width);  // 行列の列数が入力次元数

    for (int i = 0; i < n; ++i) {
        // ボックス・ミュラー法（第2回）
        double u1 = rand() * 1.0 / RAND_MAX;
        double u2 = rand() * 1.0 / RAND_MAX;
        a->array[i] = sqrt(-2 * log(u1)) * cos(2 * PI * u2) * stddev;
    }
}

void mat_array_init(Mat *a, double *array) {
    const int n = a->height * a->width;
    for (int i = 0; i < n; ++i) {
        a->array[i] = array[i];
    }
}

Mat *mat_apply_func(Mat *a, double (*func)(double x)) {
    const int n = a->height * a->width;
    Mat *mat = mat_create(a->height, a->width);
    for (int i = 0; i < n; ++i) {
        mat->array[i] = func(a->array[i]);
    }
    return mat;
}

Mat *mat_apply_func2(Mat *a, double (*func)(double x, double y), double y) {
    const int n = a->height * a->width;
    Mat *mat = mat_create(a->height, a->width);
    for (int i = 0; i < n; ++i) {
        mat->array[i] = func(a->array[i], y);
    }
    return mat;
}

void mat_apply_func_inplace(Mat *a, double (*func)(double x)) {
    const int n = a->height * a->width;
    for (int i = 0; i < n; ++i) {
        a->array[i] = func(a->array[i]);
    }
}

double mat_value(Mat *a) {
    assert(a->height == 1 && a->width == 1);
    return a->array[0];
}

Mat *mat_transpose(Mat *a) {
    const int n = a->height * a->width;
    Mat *mat = mat_create(a->width, a->height);
    for (int i = 0; i < n; ++i) {
        const int r = i / a->height;
        const int c = i % a->height;
        mat->array[c * a->width + r] = a->array[i];
    }
    return mat;
}