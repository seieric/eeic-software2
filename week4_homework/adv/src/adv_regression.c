#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "matrix.h"
#include "net.h"

#define SEED 20250107
#define MAX_EPOCH 6000
#define ALPHA 0.16
#define LEARNING_RATE 0.01
#define TEST_DATA_SIZE 30  // テスト用データの件数（学習には使わない）

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

    shuffle_data(data_size, samples);

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

    normalize_data(data_size, samples);

    // 入力層4, 隠れ層3, 出力層1のニューラルネットワークの重み行列を作成
    Mat *w3x4 = mat_create(3, 4);
    Mat *w1x3 = mat_create(1, 3);
    mat_he_init(w3x4);
    mat_he_init(w1x3);

    // バイアス行列を作成
    Mat *b3x1 = mat_create(3, 1);
    Mat *b1x1 = mat_create(1, 1);
    mat_array_init(b3x1, (double[]){0, 0, 0});
    mat_array_init(b1x1, (double[]){0});

    // 初期状態の重みを表示
    printf("initial weights:\nmatrix w3x4:\n");
    mat_print(w3x4);
    printf("matrix w1x3:\n");
    mat_print(w1x3);

    // 学習率
    printf("learning rate: %lf\n", LEARNING_RATE);
    printf("alpha: %lf\n", ALPHA);
    printf("max epoch: %d\n", MAX_EPOCH);

    // モデルのトレーニング（重みの最適化）
    int last_epoch = train(LEARNING_RATE, ALPHA, MAX_EPOCH, w3x4, w1x3, b3x1, b1x1,
                             data_size - TEST_DATA_SIZE, samples);

    printf("last epoch: %d\n", last_epoch);

    // モデルのテスト
    double eval_loss, eval_acc;
    eval(w3x4, w1x3, b3x1, b1x1, TEST_DATA_SIZE, data_size - TEST_DATA_SIZE,
         samples, &eval_loss, &eval_acc);

    printf("----------\n");
    // トレーニング後のの重みを表示
    printf("trained weights:\nmatrix w3x4:\n");
    mat_print(w3x4);
    printf("matrix w1x3:\n");
    mat_print(w1x3);
    printf("bias b3x1:\n");
    mat_print(b3x1);
    printf("bias b1x1:\n");
    mat_print(b1x1);

    printf("----------\n");
    // テスト結果を表示
    printf("eval loss: %lf\n", eval_loss);
    printf("eval accuracy: %lf\n", eval_acc);

    // 重み行列を開放
    mat_destroy(w3x4);
    mat_destroy(w1x3);

    free_data(data_size, samples);

    return 0;
}