#include "history.h"

#include <stdlib.h>
#include <string.h>

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
Command *push_command(History *his, const char *str) {
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
    return c;
}