#include <stdlib.h>
#include <string.h>

#include "history.h"

#define MAX_HISTORY 5

struct history {
    size_t max_history;
    size_t bufsize;
    size_t hsize;
    char **commands;
};

void save_history(const char *filename, History *his) {
    const char *default_history_file = "history.txt";
    if (filename == NULL) filename = default_history_file;

    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "error: cannot open %s.\n", filename);
        return;
    }

    for (int i = 0; i < his->hsize; i++) {
        fprintf(fp, "%s", his->commands[i]);
    }

    fclose(fp);
}

void push_command(History *his, const char *str) {
    strcpy(his->commands[his->hsize], str);
    his->hsize++;
}

History *init_history(size_t bufsize) {
    History *his = (History *)malloc(sizeof(History));
    *his =
        (History){.max_history = MAX_HISTORY, .bufsize = bufsize, .hsize = 0};

    his->commands = (char **)malloc(his->max_history * sizeof(char *));
    char *tmp = (char *)malloc(his->max_history * his->bufsize * sizeof(char));
    for (int i = 0; i < his->max_history; i++)
        his->commands[i] = tmp + (i * his->bufsize);
    return his;
}

size_t get_bufsize(History *his) { return his->bufsize; }

char *get_command(History *his, int i) {
    if (i >= his->hsize) return NULL;
    return his->commands[i];
}

void delete_command(History *his, int i) { his->hsize--; }