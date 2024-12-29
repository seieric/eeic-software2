#include "history.h"

#include <stdlib.h>
#include <string.h>

// 線形リスト実装

typedef struct command Command;
struct command {
    char *str;
    size_t bufsize;
    Command *next;
};

struct history {
    Command *begin;
    size_t bufsize;  // [*] : この方が効率的ですね。一部の方から指摘ありました。
};

void save_history(const char *filename, History *his) {
    const char *default_history_file = "history.txt";
    if (filename == NULL) filename = default_history_file;

    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "error: cannot open %s.\n", filename);
        return;
    }
    // [*] 線形リスト版
    for (Command *p = his->begin; p != NULL; p = p->next) {
        fprintf(fp, "%s", p->str);
    }

    fclose(fp);
}

// [*] 線形リストの末尾にpush する
void push_command(History *his, const char *str) {
    Command *c = (Command *)malloc(sizeof(Command));
    char *s = (char *)malloc(his->bufsize);
    strcpy(s, str);

    *c = (Command){.str = s, .bufsize = his->bufsize, .next = NULL};

    Command *p = his->begin;

    if (p == NULL) {
        his->begin = c;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = c;
    }
}

History *init_history(size_t bufsize) {
    History *his = (History *)malloc(sizeof(History));
    *his = (History){.begin = NULL, .bufsize = bufsize};
    return his;
}

size_t get_bufsize(History *his) { return his->bufsize; }

char *get_command(History *his, int i) {
    Command *p = his->begin;
    for (int j = 0; j < i; ++j) {
        if (p == NULL) return NULL;
        p = p->next;
    }
    if (p == NULL) return NULL;
    return p->str;
}

void delete_command(History *his, int i) {
    Command *p = his->begin;
    Command *prev = NULL;
    for (int j = 0; j < i; ++j) {
        prev = p;
        p = p->next;
    }
    if (prev == NULL) {
        his->begin = NULL;
    } else {
        prev->next = NULL;
    }
    free(p->str);
    free(p);
}

bool has_space(History *his) { return true; }