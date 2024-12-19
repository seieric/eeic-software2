#include "vector.h"

typedef struct{
    double v[4]; // 2 x 2
} Matrix;

// プロトタイプ宣言でVector型を知っている必要がある
// alpha * Ax + beta * y
Vector gemv(double alpha, Matrix A, Vector x, double beta, Vector y);
void print_matrix(Matrix m);
