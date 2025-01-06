#include "net.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "activation.h"
#include "criterion.h"
#include "data.h"
#include "matrix.h"

#define MAX_EPOCH 200
#define BATCH_SIZE 5
#define BATCH_LOG_INTERVAL 200  // バッチごとのloggingを無効化

int train(const double lr, const double alpha, const int dim, Mat *w3x4,
          Mat *w1x3, Mat *b3x1, Mat *b1x1, int data_size, Sample **samples) {
    int epoch = 0;
    const int total_batch = ceil(data_size * 1.0 / BATCH_SIZE);
    Mat *input4x1 = mat_create(4, 1);
    while (++epoch < MAX_EPOCH) {
        // 各エポックの処理
        int batch = 0;
        double epoch_loss = 0;
        while (++batch < total_batch) {
            // 各バッチの処理
            double batch_loss = 0;
            for (int i = 0; i < BATCH_SIZE; ++i) {
                const int data_id = (batch - 1) * BATCH_SIZE + i;
                // 最終バッチはデータがなくなったら終了
                if (data_id >= data_size) break;

                // forward
                // 入力行列
                double data[4] = {
                    samples[data_id]->age / 25, samples[data_id]->gender,
                    samples[data_id]->score / 100, samples[data_id]->grade / 100};
                mat_array_init(input4x1, data);

                // 入力層->隠れ層の計算
                Mat *hidden3x1 = mat_mul(w3x4, input4x1);
                mat_plus_inplace(hidden3x1, b3x1);
                // 隠れ層のReLU関数の適用
                Mat *hidden3x1_relu = mat_apply_func(hidden3x1, relu);

                // 隠れ層->出力層の計算
                Mat *output1x1 = mat_mul(w1x3, hidden3x1_relu);
                mat_plus_inplace(output1x1, b1x1);
                // 出力層のSigmoid関数の適用
                Mat *output1x1_sigmoid = mat_apply_func(output1x1, sigmoid);

                // lossの計算
                batch_loss += cross_entropy_loss(mat_value(output1x1_sigmoid),
                                                 samples[data_id]->status);

                // backforward
                // w1x3の更新
                // grad = d(loss)/d(sigmoid) * d(sigmod)/d(in) * d(in)/dw
                Mat *cse_grad1x1 = mat_apply_func2(output1x1_sigmoid,
                                                   dcross_entropy_loss_dpred,
                                                   samples[data_id]->status);
                Mat *sigmoid_grad1x1 = mat_apply_func(output1x1, dsigmoid_dx);
                double coef =
                    mat_value(cse_grad1x1) * mat_value(sigmoid_grad1x1);

                // w3x4の更新
                Mat *relu_grad3x1 = mat_apply_func(hidden3x1, drelu_dx);
                Mat *w_dot_relu1x3 = mat_dot(w1x3, relu_grad3x1);
                Mat *w_dot_relu3x1 = mat_transpose(w_dot_relu1x3);
                Mat *input1x4 = mat_transpose(input4x1);
                Mat *tmp3x4 = mat_mul(w_dot_relu3x1, input1x4);

                // 最急降下法で更新
                Mat * bdiff1x1 = mat_times_x(cse_grad1x1, coef * lr);
                mat_minus_inplace(b1x1, bdiff1x1);
                Mat * bdiff3x1 = mat_times_x(w_dot_relu3x1, coef * lr);
                mat_minus_inplace(b3x1, bdiff3x1);
                Mat *diff3x1 = mat_times_x(hidden3x1_relu, coef * lr);
                Mat *diff1x3 = mat_transpose(diff3x1);
                mat_minus_inplace(w1x3, diff1x3);
                Mat *diff3x4 = mat_times_x(tmp3x4, coef * lr);
                mat_minus_inplace(w3x4, diff3x4);

                mat_destroy(hidden3x1);
                mat_destroy(hidden3x1_relu);
                mat_destroy(output1x1);
                mat_destroy(output1x1_sigmoid);
                mat_destroy(cse_grad1x1);
                mat_destroy(sigmoid_grad1x1);
                mat_destroy(relu_grad3x1);
                mat_destroy(w_dot_relu1x3);
                mat_destroy(w_dot_relu3x1);
                mat_destroy(input1x4);
                mat_destroy(tmp3x4);
                mat_destroy(bdiff1x1);
                mat_destroy(bdiff3x1);
                mat_destroy(diff3x1);
                mat_destroy(diff1x3);
                mat_destroy(diff3x4);
            }
            epoch_loss += batch_loss;
            // logging
            if (batch % BATCH_LOG_INTERVAL == 0) {
                printf("epoch: %d, batch: %d/%d, batch_loss: %lf\n", epoch,
                       batch, total_batch, batch_loss);
            }
        }
        printf("epoch: %d, loss: %lf\n", epoch, epoch_loss / data_size);
        if (epoch_loss / data_size < alpha) break;
    }

    // 最終エポックの評価
    double loss, acc;
    eval(w3x4, w1x3, data_size, 0, samples, &loss, &acc);

    mat_destroy(input4x1);

    return epoch - 1;
}

void eval(Mat *w3x4, Mat *w1x3, int data_size, int data_index, Sample **samples,
          double *loss, double *acc) {
    *loss = 0;
    *acc = 0;
    Mat *input4x1 = mat_create(4, 1);
    const int data_end = data_size + data_index;

    printf("|Age|Gender|Score |Grade |Status|Prediction|\n");
    printf("|---|------|------|------|------|----------|\n");

    for (int i = data_index; i < data_end; ++i) {
        double data[4] = {samples[i]->age / 25, samples[i]->gender,
                          samples[i]->score / 100, samples[i]->grade / 100};
        mat_array_init(input4x1, data);

        // 入力層->隠れ層の計算
        Mat *hidden3x1 = mat_mul(w3x4, input4x1);
        // 隠れ層のReLU関数の適用
        mat_apply_func_inplace(hidden3x1, relu);

        // 隠れ層->出力層の計算
        Mat *output1x1 = mat_mul(w1x3, hidden3x1);
        // 出力層のSigmoid関数の適用
        mat_apply_func_inplace(output1x1, sigmoid);

        double out = mat_value(output1x1);
        *loss += cross_entropy_loss(out, samples[i]->status);
        double pred = (out >= 0.5) ? 1 : 0;
        *acc += (pred == samples[i]->status) ? 1 : 0;

        mat_destroy(hidden3x1);
        mat_destroy(output1x1);

        printf("|%3.0lf|%6.0lf|%6.2lf|%6.2lf|%6.0lf|%10.4f|\n", samples[i]->age,
               samples[i]->gender, samples[i]->score, samples[i]->grade,
               samples[i]->status, out);
    }
    printf("|---|------|------|------|------|----------|\n");

    *loss /= data_size;  // lossの平均値
    *acc /= data_size;   // 正解率
    mat_destroy(input4x1);
}