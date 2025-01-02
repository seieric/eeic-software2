#include "train.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "activation.h"
#include "criterion.h"
#include "data.h"
#include "matrix.h"

#define MAX_EPOCH 10000
#define BATCH_SIZE 5

double calc_norm(const int dim, double v[]) {
    double tmp = 0;
    for (int i = 0; i < dim; i++) {
        tmp += v[i] * v[i];
    }
    tmp = sqrt(tmp);
    return tmp;
}

int train(const double alpha, const int dim, Mat *w3x4, Mat *w1x3,
          int data_size, Sample **samples) {
    int epoch = 0;
    const int total_batch = data_size / BATCH_SIZE + 1;
    Mat *input4x1 = mat_create(4, 1);
    Mat *hidden3x1;
    while (++epoch < MAX_EPOCH) {
        // 各エポックの処理
        for (int batch = 0; batch < total_batch; ++batch) {
            // 各バッチの処理
            double loss = 0;
            for (int i = 0; i < BATCH_SIZE; ++i) {
                // 最終バッチはデータがなくなったら終了
                if (batch * BATCH_SIZE + i >= data_size) break;

                // forward
                // 入力行列
                const double data[4] = {samples[i]->age, samples[i]->gender,
                                        samples[i]->score, samples[i]->grade};
                mat_array_init(input4x1, data);

                // 入力層->隠れ層の計算
                hidden3x1 = mat_mul(w3x4, input4x1);
                // 隠れ層のReLU関数の適用
                mat_apply_func(hidden3x1, relu);

                // 隠れ層->出力層の計算
                Mat *output1x1 = mat_mul(w1x3, hidden3x1);
                // 出力層のSigmoid関数の適用
                mat_apply_func(output1x1, sigmoid);

                // lossの計算
                loss += cross_entropy_loss(mat_value(output1x1),
                                           samples[i]->status);
            }
            // logging
            printf("epoch: %d, batch: %d, loss: %lf\n", epoch, batch, loss);
        }
    }

    return epoch;
}