#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define RADIUS 20
#define PI 3.14159265358979323846
#define MAX_PLAYERS 4
#define MAX_ROUNDS 25

// 座標を表す. [-20,20] が描画範囲
typedef struct point {
    double x;
    double y;
} Point;

// 横方向については改行と'\0' も考慮する
typedef struct board {
    char space[2 * RADIUS + 1][4 * RADIUS + 3];
    double radius;
} Board;

// 初期化して円を表示する
//  * なにもない場所は ' 'を代入します
// 円の縁に相当する部分に'+'を代入します
void my_init_board(Board *b);

// 盤面を表示
void my_print_board(Board *b);

// ボード構造体内の配列の上限を取得
size_t my_get_board_height(Board *b);
size_t my_get_board_width(Board *b);

// i回目 (1-3) が盤面内なら数字でプロット
void my_plot_throw(Board *b, Point p, int i, int r, int player,
                   int scores[MAX_PLAYERS][MAX_ROUNDS]);

// 座標が描画領域ならtrueを返す
bool my_is_in_board(Board *b, Point p);

// 座標が有効（得点圏内）ならtrueを返す
bool my_is_valid_point(Board *b, Point p);

// 分散が等方向一定の正規分布の乱数を生成する
Point my_iso_gauss_rand(Point mu, double stddev);

// 座標を (? ?) で表示（改行なし）
void my_print_point(Point p);

int my_calculate_score(Board *b, Point p);

void my_print_score(int num_rounds, int player,
                    int scores[MAX_PLAYERS][MAX_ROUNDS]);

Point my_calculate_target(char type, int area);
double my_parse_type(char type);
double my_parse_area(int area);
