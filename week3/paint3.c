// コマンドラインペイントプログラム

#include "paint3.h"

#include <ctype.h>
#include <errno.h>  // for error catch
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    // for history recording
    const int bufsize = 1000;
    History his = (History){.begin = NULL, .bufsize = bufsize};

    int width;
    int height;
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "usage: %s <width> <height> <history_file>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        char *e;
        long w = strtol(argv[1], &e, 10);
        if (*e != '\0') {
            fprintf(stderr, "%s: irregular character found %s\n", argv[1], e);
            return EXIT_FAILURE;
        }
        long h = strtol(argv[2], &e, 10);
        if (*e != '\0') {
            fprintf(stderr, "%s: irregular character found %s\n", argv[2], e);
            return EXIT_FAILURE;
        }
        width = (int)w;
        height = (int)h;
    }

    // 履歴を読み込む
    char file[100] = "history.txt";
    if (argc == 4) {
        strcpy(file, argv[3]);
    }

    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL) {
        printf("Error: Unable to open '%s'.\n", file);
        return EXIT_FAILURE;
    }

    char pen = '*';

    char buf[his.bufsize];

    Canvas *c = init_canvas(width, height, pen);

    while (fgets(buf, his.bufsize, fp) != NULL) {
        if (strcmp(buf, "\n") == 0) break;
        his_push_back(&his, buf);
    }

    Command *com = his.begin;
    while (com) {
        interpret_command(com->str, &his, c);
        com = com->next;
    }

    printf("\n");  // required especially for windows env

    while (true) {
        size_t hsize = his_size(&his);
        size_t bufsize = his.bufsize;
        print_canvas(c);
        printf("%zu > ", hsize);
        if (fgets(buf, bufsize, stdin) == NULL) break;

        const Result r = interpret_command(buf, &his, c);

        if (r == EXIT) break;

        // 返ってきた結果に応じてコマンド結果を表示
        clear_command();
        printf("%s\n", strresult(r));
        // LINEの場合はHistory構造体に入れる
        if (r == LINE || r == RECT) {
            his_push_back(&his, buf);
        }
        rewind_screen(2);           // command results
        clear_command();            // command itself
        rewind_screen(height + 2);  // rewind the screen to command input
    }

    clear_screen();
    free_canvas(c);

    return 0;
}

Canvas *init_canvas(int width, int height, char pen) {
    Canvas *new = (Canvas *)malloc(sizeof(Canvas));
    new->width = width;
    new->height = height;
    new->canvas = (char **)malloc(width * sizeof(char *));

    char *tmp = (char *)malloc(width * height * sizeof(char));
    memset(tmp, ' ', width * height * sizeof(char));
    for (int i = 0; i < width; i++) {
        new->canvas[i] = tmp + i *height;
    }

    new->pen = pen;
    return new;
}

void reset_canvas(Canvas *c) {
    const int width = c->width;
    const int height = c->height;
    memset(c->canvas[0], ' ', width * height * sizeof(char));
}

void print_canvas(Canvas *c) {
    const int height = c->height;
    const int width = c->width;
    char **canvas = c->canvas;

    // 上の壁
    printf("+");
    for (int x = 0; x < width; x++) printf("-");
    printf("+\n");

    // 外壁と内側
    for (int y = 0; y < height; y++) {
        printf("|");
        for (int x = 0; x < width; x++) {
            const char c = canvas[x][y];
            putchar(c);
        }
        printf("|\n");
    }

    // 下の壁
    printf("+");
    for (int x = 0; x < width; x++) printf("-");
    printf("+\n");
    fflush(stdout);
}

void free_canvas(Canvas *c) {
    free(c->canvas[0]);  //  for 2-D array free
    free(c->canvas);
    free(c);
}

void rewind_screen(unsigned int line) { printf("\e[%dA", line); }

void clear_command(void) { printf("\e[2K"); }

void clear_screen(void) { printf("\e[2J"); }

int max(const int a, const int b) { return (a > b) ? a : b; }
void draw_line(Canvas *c, const int x0, const int y0, const int x1,
               const int y1) {
    const int width = c->width;
    const int height = c->height;
    char pen = c->pen;

    const int n = max(abs(x1 - x0), abs(y1 - y0));
    if ((x0 >= 0) && (x0 < width) && (y0 >= 0) && (y0 < height))
        c->canvas[x0][y0] = pen;
    for (int i = 1; i <= n; i++) {
        const int x = x0 + i * (x1 - x0) / n;
        const int y = y0 + i * (y1 - y0) / n;
        if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
            c->canvas[x][y] = pen;
    }
}

void draw_rect(Canvas *c, const int x0, const int y0, const int rect_width,
               const int rect_height) {
    const int width = c->width;
    const int height = c->height;
    char pen = c->pen;

    for (int i = 0; i < rect_height; ++i) {
        const int y = y0 + i;
        if (i == 0 || i == rect_height - 1) {
            for (int j = 0; j < rect_width; ++j) {
                const int x = x0 + j;
                if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
                    c->canvas[x][y] = pen;
            }
        } else {
            if ((x0 >= 0) && (x0 < width) && (y >= 0) && (y < height))
                c->canvas[x0][y] = pen;
            const int x1 = x0 + rect_width - 1;
            if ((x1 >= 0) && (x1 < width) && (y >= 0) && (y < height))
                c->canvas[x1][y] = pen;
        }
    }
}

void draw_circle(Canvas *c, const int x0, const int y0, const int r) {
    const int width = c->width;
    const int height = c->height;
    const char pen = c->pen;
    for (int i = 0; i <= 2 * r; ++i) {
        for (int j = 0; j <= 2 * r; ++j) {
            const int y = y0 - r + i;
            const double dx = sqrt(r * r - (i - r) * (i - r));
            const int x1 = x0 - dx;
            const int x2 = x0 + dx;
            if (y >= 0 && y < height) {
                if (x1 >= 0 && x1 < width) c->canvas[x1][y] = pen;
                if (x2 >= 0 && x2 < width) c->canvas[x2][y] = pen;
            }
        }
    }
}

void save_history(const char *filename, History *his) {
    const char *default_history_file = "history.txt";
    if (filename == NULL) filename = default_history_file;

    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "error: cannot open %s.\n", filename);
        return;
    }

    Command *com = his->begin;
    while (com) {
        fprintf(fp, "%s", com->str);
        com = com->next;
    }

    fclose(fp);
}

Result interpret_command(const char *command, History *his, Canvas *c) {
    char buf[his->bufsize];
    strcpy(buf, command);
    buf[strlen(buf) - 1] = 0;  // remove the newline character at the end

    const char *s = strtok(buf, " ");
    if (s == NULL) {  // 改行だけ入力された場合
        return UNKNOWN;
    }
    // The first token corresponds to command
    if (strcmp(s, "line") == 0) {
        int p[4] = {0};  // p[0]: x0, p[1]: y0, p[2]: x1, p[3]: x1
        char *b[4];
        for (int i = 0; i < 4; i++) {
            b[i] = strtok(NULL, " ");
            if (b[i] == NULL) {
                return ERRLACKARGS;
            }
        }
        for (int i = 0; i < 4; i++) {
            char *e;
            long v = strtol(b[i], &e, 10);
            if (*e != '\0') {
                return ERRNONINT;
            }
            p[i] = (int)v;
        }

        draw_line(c, p[0], p[1], p[2], p[3]);
        return LINE;
    }

    if (strcmp(s, "rect") == 0) {
        int p[4] = {0};  // p[0]: x0, p[1]: y0, p[2]: x1, p[3]: x1
        char *b[4];
        for (int i = 0; i < 4; i++) {
            b[i] = strtok(NULL, " ");
            if (b[i] == NULL) {
                return ERRLACKARGS;
            }
        }
        for (int i = 0; i < 4; i++) {
            char *e;
            long v = strtol(b[i], &e, 10);
            if (*e != '\0') {
                return ERRNONINT;
            }
            p[i] = (int)v;
        }

        draw_rect(c, p[0], p[1], p[2], p[3]);
        return RECT;
    }

    if (strcmp(s, "circle") == 0) {
        int p[3] = {0};  // p[0]: x0, p[1]: y0, p[2]: r
        char *b[3];
        for (int i = 0; i < 3; i++) {
            b[i] = strtok(NULL, " ");
            if (b[i] == NULL) {
                return ERRLACKARGS;
            }
        }
        for (int i = 0; i < 3; i++) {
            char *e;
            long v = strtol(b[i], &e, 10);
            if (*e != '\0') {
                return ERRNONINT;
            }
            p[i] = (int)v;
        }

        draw_circle(c, p[0], p[1], p[2]);
        return CIRCLE;
    }

    if (strcmp(s, "save") == 0) {
        s = strtok(NULL, " ");
        save_history(s, his);
        return SAVE;
    }

    if (strcmp(s, "undo") == 0) {
        reset_canvas(c);
        his_pop_back(his);
        Command *com = his->begin;
        while (com) {
            interpret_command(com->str, his, c);
            com = com->next;
        }
        return UNDO;
    }

    if (strcmp(s, "quit") == 0) {
        return EXIT;
    }

    return UNKNOWN;
}

char *strresult(Result res) {
    switch (res) {
        case EXIT:
            break;
        case SAVE:
            return "history saved";
        case LINE:
            return "1 line drawn";
        case RECT:
            return "1 rect drawn";
        case CIRCLE:
            return "1 circle drawn";
        case UNDO:
            return "undo!";
        case UNKNOWN:
            return "error: unknown command";
        case ERRNONINT:
            return "Non-int value is included";
        case ERRLACKARGS:
            return "Too few arguments";
    }
    return NULL;
}

void his_push_back(History *his, const char *command) {
    Command *new = (Command *)malloc(sizeof(Command));
    char *s = (char *)malloc(strlen(command) + 1);
    strcpy(s, command);
    *new = (Command){.str = s, .next = NULL, .bufsize = strlen(command)};

    Command *com = his->begin;
    if (com) {
        while (com->next) {
            com = com->next;
        }
        com->next = new;
    } else {
        his->begin = new;
    }
}

void his_pop_back(History *his) {
    Command *com = his->begin;
    Command *prev = NULL;
    printf("t");
    if (com) {
        while (com->next) {
            prev = com;
            com = com->next;
        }
        if (com == his->begin) {
            his->begin = NULL;
        } else {
            prev->next = NULL;
        }
        free(com->str);
        free(com);
    }
}

size_t his_size(History *his) {
    size_t size = 0;
    Command *com = his->begin;
    while (com) {
        com = com->next;
        ++size;
    }
    return size;
}