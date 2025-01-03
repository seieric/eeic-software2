#include "criterion.h"

#include <assert.h>
#include <math.h>

#define EPS 1e-7

double cross_entropy_loss(double pred, double ans) {
    assert(0 <= pred && pred <= 1);
    assert(0 <= ans && ans <= 1);
    // 0や1ではlogが計算できないのでクリップして回避する
    if (pred < EPS) pred = EPS;
    if (pred > 1 - EPS) pred = 1 - EPS;
    return -ans * log2(pred) - (1 - ans) * log2(1 - pred);
}

double dcross_entropy_loss_dpred(double pred, double ans) {
    return -ans / pred + (1 - ans) / (1 - pred);  // 定数は無視
}