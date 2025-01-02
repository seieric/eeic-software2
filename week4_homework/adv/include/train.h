#pragma once
#include "data.h"
#include "matrix.h"
int train(const double alpha, const int dim, Mat *w3x4, Mat *w1x3,
          int data_size, Sample **samples);