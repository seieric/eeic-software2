typedef struct {
    double v[2];
} Vector;

// ax + y の形（BLASレベル1と同じ名前のつけかた）
Vector axpy(double alpha, Vector a, Vector b);
void print_vector(Vector a);
