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
typedef struct history History;

void save_history(const char *filename, History *his);

// [*] list.c のpush_backと同じ
Command *push_command(History *his, const char *str);

History *init_history(size_t bufsize);

size_t get_bufsize(History *his);

Command *get_begin(History *his);
Command *set_begin(History *his, Command *c);