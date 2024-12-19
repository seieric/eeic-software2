/*
 * 標準ライブラリ関数qsortを使ってみる
 */
#include "initlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // strtol のエラー判定用
#include <string.h> // strerror(errno) のため

int main(int argc, char **argv)
{
    if(argc != 2){
	fprintf(stderr, "usage: %s <number of elements>\n",argv[0]);
	exit(EXIT_FAILURE);
    }
    
    int n = load_int(argv[1]);
    
    int *v = (int*) malloc(sizeof(int) * n);
    errno = 0;
    if (v == NULL){
	fprintf(stderr, "Error: %s\n",strerror(errno));
	exit(EXIT_FAILURE);
    }
    
    for(int i = 0 ; i < n ; i++){
	v[i] = rand()%1024;// 0 - 1023 で値を入れる
    }
    
    // sort前表示
    printf("[");
    for(int i = 0 ; i < n ; i++){
	printf("%d ",v[i]);
    }
    printf("]\n");
    
    // qsort実行
    qsort(v, n, sizeof(int), comp_int);
    
    // sort後表示
    for (int i = 0; i < n; i++) {
	printf("v[%d] = %d\n", i, v[i]);
    }
    
    free(v);
    return 0;
}
