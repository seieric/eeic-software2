#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "func.h"
#include "optimize.h"

#define BUF_SIZE 1000

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        printf("usage: %s <csv file> <alpha>\n", argv[0]);
        return 1;
    }

    Sample **samples = NULL;
    int data_size = load_data(argv[1], samples);
    if (data_size == 0) {
        printf("error: unable to load data.\n");
        return 1;
    }

    for (int i = 0; i < data_size; ++i) {
        printf("Location: , Altitude: %lf, Temperature: %lf\n", samples[i]->alt,
               samples[i]->temp);
        fflush(stdout);
    }

    // 引数の個数が2の時だけ、alpha に第2引数を採用し、それ以外は0.01
    const double alpha = (argc == 3) ? atof(argv[2]) : 0.01;

    const int dim = f_dimension();

    double *x = malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++) {
        x[i] = 0;
    }

    printf("alpha = %f\n", alpha);

    const int iter = optimize(alpha, dim, x, f_gradient, data_size, samples);

    printf("number of iterations = %d\n", iter);

    free(x);

    return 0;
}