#include <stdio.h>
#include "matrix.h"
#include "vector.h"

Vector gemv(double alpha, Matrix A, Vector x, double beta, Vector y)
{
    return (Vector){ .v = {alpha * (A.v[0]*x.v[0]+A.v[1]*x.v[1]) + beta * y.v[0], alpha * (A.v[2]*x.v[0]+A.v[3]*x.v[1]) + beta * y.v[1]}};
}

void print_matrix(Matrix m)
{
    printf("[%f %f ;%f %f]\n",m.v[0],m.v[1],m.v[2],m.v[3]);    
}
