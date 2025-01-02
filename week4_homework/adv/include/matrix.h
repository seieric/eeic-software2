typedef struct mat Mat;

Mat *mat_mul(Mat *a, Mat *b);
Mat *mat_create(const int height, const int width, double array[]);
void mat_destroy(Mat *a);
void mat_print(Mat *a);