#include <math.h>
#include <stdbool.h>
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

        my_plot_throw(&board, p, i);
        my_print_board(&board);
        printf("-------\n");
        my_print_point(p);
        if (!my_is_valid_point(&board, p)) printf(" miss!");
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

void my_plot_throw(Board *b, Point p, int i) {
    if (my_is_in_board(b, p)) {
        int h = round(p.y + 20);
        int w = round(2 * (p.x + 20));
        b->space[h][w] = i + '0';
    }
}

bool my_is_in_board(Board *b, Point p) {
    // 描画範囲[-20, 20]に含まれるならtrueを返す
    if (-20 <= p.x && p.x <= 20 && -20 <= p.y && p.y <= 20) {
        return true;
    }

    return false;
}

bool my_is_valid_point(Board *b, Point p) {
    if (!my_is_in_board(b, p)) return false;

    int h = round(p.y + 20);
    int w = round(2 * (p.x + 20));
    int count = 0;
    for (int i = 0; i <= w; ++i) {
        if (b->space[h][i] == '+') ++count;
    }
    if (count == 1) return true;
    return false;
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
        double dx = w_center * sqrt((1 - pow((i - h_center) * 1.0 / h_center, 2)));
        int x1 = w_center - dx;
        int x2 = w_center + dx;
        b->space[i][x1] = '+';
        b->space[i][x2] = '+';
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

void my_print_point(Point p) { printf("(%f %f)", p.y, p.x); }
