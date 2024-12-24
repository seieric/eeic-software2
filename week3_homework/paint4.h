#include <stdlib.h>

// コピー・切り取り領域用構造体
typedef struct {
    int width;
    int height;
    char **canvas;
} ClipBoard;

// Structure for canvas
typedef struct {
    int width;
    int height;
    char **canvas;
    char pen;
    ClipBoard *clipboard; // クリップボード
} Canvas;

// 最大履歴と現在位置の情報は持たない
typedef struct command Command;
struct command {
    char *str;
    size_t bufsize;
    Command *next;
};

// コマンドリストの先頭へのポインタをメンバに持つ構造体としてHistoryを考える。
// 履歴がない時点ではbegin = NULL となる。
typedef struct {
    Command *begin;
    size_t bufsize;
} History;

void his_push_back(History *his, const char *str);
void his_pop_back(History *his);
size_t his_size(History *his);

// 塗りつぶし用のスタック
typedef struct point Point;
struct point {
    int x;
    int y;
    Point *next;
};
typedef struct {
    Point *begin;
} PointStack;

void ps_push_back(PointStack *ps, const int x, const int y);
Point ps_pop_back(PointStack *ps);
size_t ps_size(PointStack *ps);

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
    RECT,
    CIRCLE,
    CHPEN,
    FILL,
    COPY,
    PASTE,
    UNDO,
    SAVE,
    LOAD_SUCCESS,
    LOAD_ERROR,
    UNKNOWN,
    ERRNONINT,
    ERRLACKARGS,
    ERRINVALIDVALUE,
} Result;
// Result 型に応じて出力するメッセージを返す
char *strresult(Result res);

int max(const int a, const int b);
int min(const int a, const int b);
void draw_line(Canvas *c, const int x0, const int y0, const int x1,
               const int y1);
void draw_rect(Canvas *c, const int x0, const int y0, const int rect_width,
               const int rect_height);
void draw_circle(Canvas *c, const int x0, const int y0, const int r);
void fill_area(Canvas *c, const int x0, const int y0);
void scan_span(Canvas *c, char pen, int lx, const int rx, const int y,
               PointStack *ps);
void copy_rect(Canvas *c, const int x0, const int y0, const int rect_width,
               const int rect_height);
void paste_rect(Canvas *c, const int x0, const int y0);
Result interpret_command(const char *command, History *his, Canvas *c);
void save_history(const char *filename, History *his);