#include <stdio.h>

#include "data.h"

int f_dimension() { return 2; }

double f_value(const double x[], int data_size, Sample *samples[data_size]) {
    double sum = 0.0;
    for (int i = 0; i < data_size; ++i) {
        sum += (samples[i]->temp - x[0] * samples[i]->alt - x[1]) *
               (samples[i]->temp - x[0] * samples[i]->alt - x[1]);
    }
    return sum;
}

void f_gradient(const double x[], double g[], int data_size,
                Sample *samples[data_size]) {
    g[0] = 0.0;
    g[1] = 0.0;
    for (int i = 0; i < data_size; ++i) {
        g[0] += -2 * (samples[i]->temp - x[0] * samples[i]->alt - x[1]) * samples[i]->alt;
        g[1] += -2 * (samples[i]->temp - x[0] * samples[i]->alt - x[1]);
    }
}
