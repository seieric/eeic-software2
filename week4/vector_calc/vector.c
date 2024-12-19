#include <stdio.h>
#include "vector.h"

#ifndef _VECTOR_H
#define _VECTOR_H
Vector axpy(double alpha, Vector a, Vector b)
{
    return (Vector){ .v = { alpha * a.v[0] + b.v[0], alpha * a.v[1] + b.v[1]}};
}

void print_vector(Vector a)
{
    printf("[%f %f]\n",a.v[0],a.v[1]);
}
#endif
