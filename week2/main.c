#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "darts.h"

int main(int argc, char **argv) {
    Board board;

    srand((unsigned int)time(NULL));

    my_init_board(&board);

    // 3回投げる
    for (int i = 1; i <= 3; i++) {
        Point p = my_iso_gauss_rand((Point){.x = 0, .y = 0}, 15.0);

        plot_throw(&board, p, i);
        my_print_board(&board);
        printf("-------\n");
        my_print_point(p);
        if (!is_valid_point(&board, p)) printf(" miss!");
        printf("\n");
        sleep(1);
    }
    return 0;
}

void my_print_board(Board *b) {
    int height = my_get_board_height(b);
    int width = my_get_board_width(b);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%c", b->space[i][j]);
        }
    }
}

size_t my_get_board_height(Board *b) {
    return sizeof(b->space) / sizeof(b->space[0]);
}

size_t my_get_board_width(Board *b) {
    return sizeof(b->space[0]) / sizeof(char);
}

void my_init_board(Board *b) {
    int height = my_get_board_height(b);
    int width = my_get_board_width(b);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width - 2; ++j) {
            b->space[i][j] = ' ';
        }
        b->space[i][width - 2] = '\n';
        b->space[i][width - 1] = '\0';
    }

    printf("%d %d", width, height);
    for (int i = 0; i < height; ++i) {
        int w_center = (width - 2) / 2;
        int h_center = height / 2;
        int dx = w_center * sqrt((1 - pow((i - h_center) * 1.0 / h_center, 2)));
        b->space[i][w_center - dx] = '+';
        b->space[i][w_center + dx] = '+';
    }
}

Point my_iso_gauss_rand(Point mu, double stddev) {
    srand((unsigned int)time(NULL));

    double u1 = rand() * 1.0 / RAND_MAX;
    double u2 = rand() * 1.0 / RAND_MAX;
    double x = sqrt(-2 * log(u1)) * cos(2 * PI * u1) * stddev + mu.x;
    double y = sqrt(-2 * log(u2)) * sin(2 * PI * u2) * stddev + mu.y;
    return (Point){.x = x, .y = y};
}

void my_print_point(Point p) { printf("(%f %f)", p.x, p.y); }
