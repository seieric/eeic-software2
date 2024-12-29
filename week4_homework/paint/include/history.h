#pragma once
#include <stdio.h>
// Command 構造体と History構造体
// [*]
typedef struct command Command;
struct command {
    char *str;
    size_t bufsize;
    Command *next;
};

typedef struct {
    Command *begin;
    size_t bufsize;  // [*] : この方が効率的ですね。一部の方から指摘ありました。
} History;

void save_history(const char *filename, History *his);

// [*] list.c のpush_backと同じ
Command *push_command(History *his, const char *str);