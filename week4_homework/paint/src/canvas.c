#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Canvas *init_canvas(int width, int height, char pen) {
    Canvas *new = (Canvas *)malloc(sizeof(Canvas));
    new->width = width;
    new->height = height;
    new->canvas = (char **)malloc(width * sizeof(char *));

    char *tmp = (char *)malloc(width * height * sizeof(char));
    memset(tmp, ' ', width * height * sizeof(char));
    for (int i = 0; i < width; i++) {
        new->canvas[i] = tmp + i *height;
    }

    new->pen = pen;
    return new;
}

void reset_canvas(Canvas *c) {
    const int width = c->width;
    const int height = c->height;
    memset(c->canvas[0], ' ', width * height * sizeof(char));
}

void print_canvas(Canvas *c) {
    const int height = c->height;
    const int width = c->width;
    char **canvas = c->canvas;

    // 上の壁
    printf("+");
    for (int x = 0; x < width; x++) printf("-");
    printf("+\n");

    // 外壁と内側
    for (int y = 0; y < height; y++) {
        printf("|");
        for (int x = 0; x < width; x++) {
            const char c = canvas[x][y];
            putchar(c);
        }
        printf("|\n");
    }

    // 下の壁
    printf("+");
    for (int x = 0; x < width; x++) printf("-");
    printf("+\n");
    fflush(stdout);
}

void free_canvas(Canvas *c) {
    free(c->canvas[0]);  //  for 2-D array free
    free(c->canvas);
    free(c);
}