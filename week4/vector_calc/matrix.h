#ifndef _MATRIX_H_
#define _MATRIX_H_
#include "vector.h"

typedef struct{
    double v[4]; // 2 x 2
} Matrix;

// プロトタイプ宣言でVector型を知っている必要があ　る
// alpha * Ax + beta * y
Vector gemv(double alpha, Matrix A, Vector x, double beta, Vector y);
void print_matrix(Matrix m);
#endif