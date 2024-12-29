#pragma once
// Structure for canvas
typedef struct {
    int width;
    int height;
    char **canvas;
    char pen;
} Canvas;

// functions for Canvas type
Canvas *init_canvas(int width, int height, char pen);
void reset_canvas(Canvas *c);
void print_canvas(Canvas *c);
void free_canvas(Canvas *c);