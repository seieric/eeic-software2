#pragma once
#include "data.h"
int f_dimension();
double f_value(const double x[], int data_size, Sample **samples);
void f_gradient(const double x[], double g[], int data_size, Sample **samples);