#include <stdio.h>

int add_one(int x){
    return x+1;
}

int main(){
    int (*fp)(int);
    // fp に add_one関数のアドレスを代入
    fp = &add_one;
    
    int x = 1;
    // fp で指されている関数を呼び出す
    int y = (*fp)(x);
    
    printf("%d\n", y);
    
    return 0;
}