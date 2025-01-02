#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "matrix.h"
#include "train.h"

#define SEED 1234

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        printf("usage: %s <csv file> <alpha>\n", argv[0]);
        return 1;
    }

    srand(SEED);

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

    printf("data size: %d\n\n", data_size);

    // 入力層4, 隠れ層3, 出力層1のニューラルネットワークの重み行列を作成
    Mat *w3x4 = mat_create(3, 4);
    Mat *w1x3 = mat_create(1, 3);
    mat_he_init(w3x4);
    mat_he_init(w1x3);

    // 初期状態の重みを表示
    printf("initial weights:\nmatrix w3x4:\n");
    mat_print(w3x4);
    printf("matrix w1x3:\n");
    mat_print(w1x3);

    // モデルのトレーニング（重みの最適化）
    int last_epoch = train(0, 0, w3x4, w1x3, data_size, samples);

    printf("last epoch: %d\n", last_epoch);

    // 重み行列を開放
    mat_destroy(w3x4);
    mat_destroy(w1x3);

    free_data(data_size, samples);

    return 0;
}