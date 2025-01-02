#include "matrix.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
