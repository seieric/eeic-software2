#include <stdio.h>

#include "data.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        printf("usage: %s <csv file> <alpha>\n", argv[0]);
        return 1;
    }

    int data_size;
    Sample **samples = load_data(argv[1], &data_size);
    if (data_size == 0) {
        printf("error: unable to load data.\n");
        return 1;
    }

    printf("|Name      |Age|Gender|Score |Grade |City        |Status|\n");
    printf("|----------|---|------|------|------|------------|------|\n");
    for (int i = 0; i < data_size; ++i) {
        printf("|%10s|%3.0lf|%6.0lf|%6.2lf|%6.2lf|%12s|%6.0lf|\n",
               samples[i]->name, samples[i]->age, samples[i]->gender,
               samples[i]->score, samples[i]->grade, samples[i]->city,
               samples[i]->status);
    }
    printf("|----------|---|------|------|------|------------|------|\n");

    // 入力層4, 隠れ層3, 出力層1のニューラルネットワークの重み行列を作成
    Mat *w4x3 = mat_create(4, 3);
    Mat *w3x1 = mat_create(3, 1);
    mat_he_init(w4x3);
    mat_he_init(w3x1);

    // 初期状態の重みを表示
    printf("Matrix w4x3:\n");
    mat_print(w4x3);
    printf("Matrix w3x1:\n");
    mat_print(w3x1);

    // 重み行列を開放
    mat_destroy(w4x3);
    mat_destroy(w3x1);

    free_data(data_size, samples);

    return 0;
}