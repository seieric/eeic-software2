#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "func.h"
#include "optimize.h"

#define MTFUJI_ALT 3.776

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

    printf("|Location       |Altitude   |Temperature|\n");
    printf("|---------------|-----------|-----------|\n");
    for (int i = 0; i < data_size; ++i) {
        printf("|%15s|%11lf|%11lf|\n", samples[i]->loc, samples[i]->alt,
               samples[i]->temp);
    }
    printf("|---------------|-----------|-----------|\n\n");

    // 引数の個数が2の時だけ、alpha に第2引数を採用し、それ以外は0.01
    const double alpha = (argc == 3) ? atof(argv[2]) : 0.01;

    const int dim = f_dimension();

    // x[0]: a, x[1]: b (y=ax+b)
    double *x = malloc(2 * sizeof(double));
    x[0] = 0;
    x[1] = 0;

    printf("alpha = %f\n", alpha);

    const int iter = optimize(alpha, dim, x, f_gradient, f_value, data_size, samples);

    printf("number of iterations = %d\n", iter);

    printf("-----\n");
    printf("Estimated temperature of Mt. Fuji (altitude: 3.776km): %lf\n", MTFUJI_ALT * x[0] + x[1]);

    free(x);

    for (int i = 0; i < data_size; ++i) {
        free(samples[i]->loc);
        free(samples[i]);
    }
    free(samples);

    return 0;
}