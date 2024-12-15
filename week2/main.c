#include <stdio.h>
#include <stdlib.h>
#include "darts.h"
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv){
    Board board;

    srand((unsigned int)time(NULL));

    init_board(&board);

    // 3回投げる
    for (int i = 1 ; i <= 3 ; i++){
        Point p = iso_gauss_rand((Point){.x = 0, .y = 0}, 15.0);

        plot_throw(&board,p,i);
        print_board(&board);
        printf("-------\n");
        print_point(p);
        if (!is_valid_point(&board, p)) printf(" miss!");
        printf("\n");
        sleep(1);
    }
    return 0;
}
