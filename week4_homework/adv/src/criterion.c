#include "criterion.h"

#include <math.h>

double cross_entropy_loss(double pred, double ans) {
    assert(0 < pred && pred < 1);
    assert(0 <= ans && ans <= 1);
    return -ans * log2(pred) - (1 - ans) * log2(1 - pred);
}