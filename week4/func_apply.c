#include <stdio.h>

int add(int x, int y) {
    return x + y;
}

int mul(int x, int y) {
    return x * y;
}

void apply(int v[], int n, int y, int (*fp)(int,int)) {
    for (int i = 0 ; i < n ; i++){
        v[i] = (*fp)(v[i],y);
    }
}

int main() {
    int v[10];
    const int n = sizeof(v)/sizeof(int);
    for (int i = 0 ; i < n ; i++){
        v[i] = i;
    }
    
    apply(v, n, 2, add);
    apply(v, n, 3, mul);
    
    for (int i = 0 ; i < n ; i++){
        printf("v[%d] = %d\n", i, v[i]);
    }
}