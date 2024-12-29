#pragma once
#include "data.h"
int optimize(const double alpha, const int dim, double x[],
             void (*calc_grad)(const double[], double[], int, Sample **),
             int data_size, Sample **samples);