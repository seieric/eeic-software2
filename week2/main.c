#include <stdio.h>
#include <stdlib.h>
#include "darts.h"
#include <unistd.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv)
{
    Board board;

    srand((unsigned int)time(NULL));

    my_init_board(&board);

    // 3回投げる
    for (int i = 1; i <= 3; i++)
    {
        Point p = my_iso_gauss_rand((Point){.x = 0, .y = 0}, 3.0);

        plot_throw(&board, p, i);
        my_print_board(&board);
        printf("-------\n");
        my_print_point(p);
        if (!is_valid_point(&board, p))
            printf(" miss!");
        printf("\n");
        sleep(1);
    }
    return 0;
}

void my_print_board(Board *b)
{
    int height = my_get_board_height(b);
    int width = my_get_board_width(b);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            printf("%c", b->space[i][j]);
        }
    }
}

void my_init_board(Board *b)
{
    int height = my_get_board_height(b);
    int width = my_get_board_width(b);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width - 2; ++j)
        {
            b->space[i][j] = ' ';
        }
        b->space[i][width - 2] = '\n';
        b->space[i][width - 1] = '\0';
    }

    for (int i = 0; i < height; ++i)
    {
        int rad = height / 2;
        int center = width / 2;
        int x1 = center - sqrt(rad * rad - (i - rad) * (i - rad) / 4);
        int x2 = center + sqrt(rad * rad - (i - rad) * (i - rad) / 4);
        b->space[i][x1] = '+';
        b->space[i][x2] = '+';
    }
}

void my_print_point(Point p)
{
    printf("(%f %f)\n", p.x, p.y);
}

Point my_iso_gauss_rand(Point mu, double stddev)
{
    srand((unsigned int)time(NULL));

    double u1 = rand() * 1.0 / RAND_MAX;
    double u2 = rand() * 1.0 / RAND_MAX;
    double x = sqrt(-2 * log(u1)) * cos(2 * 3.141592 * u1) * stddev + mu.x;
    double y = sqrt(-2 * log(u2)) * sin(2 * 3.141592 * u2) * stddev + mu.y;
    Point p = {.x = x, .y = y};
    return p;
}

size_t my_get_board_height(Board *b)
{
    return sizeof(b->space) / sizeof(b->space[0]);
}

size_t my_get_board_width(Board *b)
{
    return sizeof(b->space[0]) / sizeof(char);
}
