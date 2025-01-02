#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct mat {
    int height;
    int width;
    double *array;
};

Mat *mat_mul(Mat *a, Mat *b) {
    assert(a->width == b->height);
    const int h = a->height;
    const int w = b->width;
    double *array = (double *)malloc(h * w * sizeof(double));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            double sum = 0;
            for (int k = 0; k < a->width; ++k) {
                sum += a->array[i * a->width + k] * b->array[j + k * w];
            }
            array[i * w + j] = sum;
        }
    }
    return mat_create(h, w, array);
}

Mat *mat_create(const int height, const int width, double *array) {
    Mat *mat = (Mat *)malloc(sizeof(Mat));
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
