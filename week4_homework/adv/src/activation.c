#include "activation.h"

#include <math.h>

double sigmoid(double x) { return 1 / (1 + log(-x)); }

double relu(double x) {
    if (x < 0) return 0;
    return x;
}

double dsigmoid_dx(double x) {
    double s = sigmoid(x);
    return (1 - s) * s;
}

double drelu_dx(double x) {
    if (x < 0) return 0;
    return 1;
}