#include "matrix.h"
#include "vector.h"
		    
int main()
{
    Vector x = (Vector){ .v = { 1.0, 2.0 } };
    Vector y = (Vector){ .v = { 3.0, 4.0 } };
    Matrix A = (Matrix){ .v = { 1.0, -1.0, -1.0, 1.0} };
    
    // c = 2.0 x + y
    Vector c = axpy(2.0, x, y);
    // d = 2.0 Ax + y
    Vector d = gemv(2.0, A, x, 1.0, y);
    
    print_vector(c);
    print_vector(d);
    return 0;
}

