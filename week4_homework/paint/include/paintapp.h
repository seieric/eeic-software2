#include <stdio.h>

#include "canvas.h"
#include "history.h"

// enum for interpret_command results
typedef enum res {
    EXIT,
    LINE,
    UNDO,
    SAVE,
    UNKNOWN,
    ERRNONINT,
    ERRLACKARGS,
    NOCOMMAND
} Result;
// Result 型に応じて出力するメッセージを返す
char *strresult(Result res);

int max(const int a, const int b);
void draw_line(Canvas *c, const int x0, const int y0, const int x1,
               const int y1);
Result interpret_command(const char *command, History *his, Canvas *c);