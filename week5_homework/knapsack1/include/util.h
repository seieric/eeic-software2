#pragma once
#include <stdbool.h>

// エラー判定付きの読み込み関数
int load_int(const char *argvalue);
double load_double(const char *argvalue);
// 文字列が整数かどうか判定する関数
bool is_int(char *str);
