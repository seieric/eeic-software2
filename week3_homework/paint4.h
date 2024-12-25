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
    ClipBoard *clipboard;  // クリップボード
} Canvas;

// 最大履歴と現在位置の情報は持たない
typedef struct command Command;
struct command {
    char *str;
    size_t bufsize;
    Command *prev;
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
    CUT,
    PASTE,
    UNDO,
    SAVE,
    SAVETXT,
    SAVEBMP,
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

// 描画機能
void draw_line(Canvas *c, const int x0, const int y0, const int x1,
               const int y1);
void draw_rect(Canvas *c, const int x0, const int y0, const int rect_width,
               const int rect_height);
void draw_circle(Canvas *c, const int x0, const int y0, const int r);
void fill_area(Canvas *c, const int x0, const int y0);
void scan_span(Canvas *c, char pen, int lx, const int rx, const int y,
               PointStack *ps);

// コピー（カット）＆ペースト
void copy_rect(Canvas *c, const int x0, const int y0, const int rect_width,
               const int rect_height);
void cut_rect(Canvas *c, const int x0, const int y0, const int rect_width,
              const int rect_height);
void paste_rect(Canvas *c, const int x0, const int y0);

Result interpret_command(const char *command, History *his, Canvas *c);

// 保存機能
void save_history(const char *filename, History *his);
void save_text(const char *filename, Canvas *c);
void save_bitmap(const char *filename, Canvas *c);

// ビットマップ用
#pragma pack(push, 1)
// ファイルヘッダ
typedef struct {
    unsigned short type;       // ファイルタイプ（2バイト）
    unsigned int size;         // ファイルサイズ（4バイト）
    unsigned short reserved1;  // 予約領域1（2バイト）
    unsigned short reserved2;  // 予約領域2（2バイト）
    unsigned int offbits;      // 画像データの位置（4バイト）
} BitmapFileHeader;

// 情報ヘッダ（INFOタイプ）
typedef struct {
    unsigned int size;          // ヘッダのサイズ（4バイト）
    int image_width;            // 画像幅（4バイト）
    int image_height;           // 画像高さ（4バイト）
    unsigned short num_planes;  // チャンネル数（2バイト）
    unsigned short num_bits;  // ピクセルあたりのビット数（2バイト）
    unsigned int compress_type;  // 圧縮タイプ（4バイト）
    unsigned int image_size;     // 画像のバイト数（4バイト）
    unsigned int x_ppm;  // 水平方向1メートルあたりのピクセル数（4バイト）
    unsigned int y_ppm;  // 垂直方向1メートルあたりのピクセル数（4バイト）
    unsigned int num_colors;  // カラーパレットに格納される色数（4バイト）
    unsigned int
        num_sig_colors;  // カラーパレットに格納される色のうち重要色の数（4バイト）
} BitmapInfoHeader;

// カラー
typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved;
} BitmapRGBQUAD;
#pragma pack(pop)

void init_bitmapfileheader(BitmapFileHeader *);
void init_bitmapinfoheader(const int, const int, BitmapInfoHeader *);
void init_bitmaprgbquad(const unsigned char r, const unsigned char g,
                        const unsigned char b, BitmapRGBQUAD *color);