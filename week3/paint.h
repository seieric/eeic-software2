#include <stdlib.h>

// Structure for canvas
typedef struct {
    int width;
    int height;
    char **canvas;
    char pen;
} Canvas;

// Structure for history (2-D array)
typedef struct {
    size_t max_history;
    size_t bufsize;
    size_t hsize;
    char **commands;
} History;

// functions for Canvas type
Canvas *init_canvas(int width, int height, char pen);
void reset_canvas(Canvas *c);
void print_canvas(Canvas *c);
void free_canvas(Canvas *c);

// display functions
void rewind_screen(unsigned int line);
void clear_command(void);
void clear_screen(void);

// enum for interpret_command results
// interpret_command の結果をより詳細に分割
typedef enum res {
    EXIT,
    LINE,
    UNDO,
    SAVE,
    UNKNOWN,
    ERRNONINT,
    ERRLACKARGS
} Result;
// Result 型に応じて出力するメッセージを返す
char *strresult(Result res);

int max(const int a, const int b);
void draw_line(Canvas *c, const int x0, const int y0, const int x1,
               const int y1);
Result interpret_command(const char *command, History *his, Canvas *c);
void save_history(const char *filename, History *his);