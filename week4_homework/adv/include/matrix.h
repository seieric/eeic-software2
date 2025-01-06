// 行列計算
#pragma once
typedef struct mat Mat;

Mat *mat_mul(Mat *a, Mat *b);
Mat *mat_dot(Mat *a, Mat *b);
Mat *mat_times_x(Mat *a, double x);
void mat_plus_inplace(Mat *a, Mat *b);
void mat_minus_inplace(Mat *a, Mat *b);
Mat *mat_create(const int height, const int width);
void mat_destroy(Mat *a);
void mat_print(Mat *a);

// 初期化
void mat_he_init(Mat *a);
void mat_array_init(Mat *a, double *array);

// 各要素への関数適用
Mat *mat_apply_func(Mat *a, double (*func)(double x));
void mat_apply_func_inplace(
    Mat *a,
    double (*func)(double x));  // 引数の行列を書き換える
Mat *mat_apply_func2(Mat *a, double (*func)(double x, double y), double y);

// 1x1行列の値
double mat_value(Mat *a);

// 転置
Mat *mat_transpose(Mat *a);