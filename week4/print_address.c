#include <stdio.h>
#include <stdlib.h>

int global = 0;

int add_one(int x){

    // 静的領域に変数を確保する
    static int count = 0;
    
    // 関数内のstatic変数	
    printf("count_in_add_one(%d): %p\n", count,&count);
    // add_one関数の引数x
    printf("x_in_add_one(%d): %p\n",count,&x);
    
    count++; // 何回呼び出されたかを記録
    return x + 1;
}

void call(int x, int (*fp)(int)){
    // call関数の引数x
    printf("x_in_call: %p\n",&x);
    // call関数の引数fp
    printf("fp_in_call: %p\n", &fp);
    
    fp(x);
}

int main(int argc, char **argv){
    int x = 10;
    int *a = (int*) malloc(sizeof(int));
    
    // main関数のアドレス
    printf("function_main: %p\n", &main);
    
    // main内の変数x
    printf("x_in_main: %p\n", &x);
    
    // argc
    printf("argc_in_main: %p\n", &argc);
    
    // argv
    printf("argv_in_main: %p\n", &argv);
    
    // グローバル変数global
    printf("global: %p\n", &global);
    
    // malloc されたa
    printf("allocated_a: %p\n", a);
    // ポインタそのもののアドレス
    
    printf("pointer_a_in_main: %p\n", &a);
    
    add_one(x);
    
    // add_one関数のアドレス
    printf("function_add_one: %p\n", &add_one);
    
    // もう一度呼ぶ
    add_one(x);
    
    // call 経由でadd_one を呼ぶ
    call(x,add_one);

    // call関数のアドレス
    printf("function_call: %p\n", &call);
    
    free(a);
    return 0;
}