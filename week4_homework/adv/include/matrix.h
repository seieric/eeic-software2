// 行列計算
#pragma once
typedef struct mat Mat;

Mat *mat_mul(Mat *a, Mat *b);
Mat *mat_create(const int height, const int width);
void mat_destroy(Mat *a);
void mat_print(Mat *a);

// 初期化
void mat_he_init(Mat *a);