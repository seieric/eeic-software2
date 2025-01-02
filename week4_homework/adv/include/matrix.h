// 行列計算
#pragma once
typedef struct mat Mat;

Mat *mat_mul(Mat *a, Mat *b);
Mat *mat_dot(Mat *a, Mat *b);
Mat *mat_create(const int height, const int width);
void mat_destroy(Mat *a);
void mat_print(Mat *a);

// 初期化
void mat_he_init(Mat *a);
void mat_array_init(Mat *a, double *array);

// 各要素への関数適用
void mat_apply_func(Mat *a, double (*func)(double x));

// 1x1行列の値
double mat_value(Mat *a);