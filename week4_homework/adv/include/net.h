#pragma once
#include "data.h"
#include "matrix.h"
int train(const double lr, const double alpha, const int dim, Mat *w3x4,
          Mat *w1x3, Mat *b3x1, Mat *b1x1, int data_size, Sample **samples);
void eval(Mat *w3x4, Mat *w1x3, int data_size, int data_index, Sample **samples,
          double *loss, double *acc);