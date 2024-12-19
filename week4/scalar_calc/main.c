// 四則演算のプログラム
#include <stdio.h>

double add(double a,double b);
double sub(double a,double b);
double mul(double a, double b);
double div(double a, double b);

int main()
{
    double a = 1.2;
    double b = 1.4;
    
    printf("a+b: %f\n",add(a,b));
    printf("a-b: %f\n",sub(a,b));
    printf("a*b: %f\n",mul(a,b));
    printf("a/b: %f\n",div(a,b));
    return 0;
}

double add(double a, double b){
    return a + b;
}

double sub(double a, double b){
    return a - b;
}

double mul(double a, double b){
    return a * b;
}

double div(double a, double b){
    return a / b;
}
