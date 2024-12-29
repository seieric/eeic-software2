#include "paintapp.h"

#include <ctype.h>
#include <errno.h>  // for error catch
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.h"
#include "display.h"
#include "history.h"

int main(int argc, char **argv) {
    // for history recording

    const int bufsize = 1000;

    History *his = init_history(bufsize);

    int width;
    int height;
    if (argc != 3) {
        fprintf(stderr, "usage: %s <width> <height>\n", argv[0]);
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
    char pen = '*';

    char buf[bufsize];

    Canvas *c = init_canvas(width, height, pen);

    printf("\n");  // required especially for windows env

    while (1) {
        // [*]
        // hsize はひとまずなし
        // 作る場合はリスト長を調べる関数を作っておく
        print_canvas(c);
        printf("* > ");
        if (fgets(buf, bufsize, stdin) == NULL) break;

        const Result r = interpret_command(buf, his, c);

        if (r == EXIT) break;

        // 返ってきた結果に応じてコマンド結果を表示
        clear_command();
        printf("%s\n", strresult(r));
        // LINEの場合はHistory構造体に入れる
        if (r == LINE) {
            // [*]
            push_command(his, buf);
        }

        rewind_screen(2);           // command results
        clear_command();            // command itself
        rewind_screen(height + 2);  // rewind the screen to command input
    }

    clear_screen();
    free_canvas(c);

    return 0;
}

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

Result interpret_command(const char *command, History *his, Canvas *c) {
    char buf[get_bufsize(his)];
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

    if (strcmp(s, "save") == 0) {
        s = strtok(NULL, " ");
        save_history(s, his);
        return SAVE;
    }

    if (strcmp(s, "undo") == 0) {
        reset_canvas(c);
        char *str = get_command(his, 0);
        if (str == NULL) {
            return NOCOMMAND;
        } else {
            char *next;
            for (int i = 0;; ++i) {
                if ((next = get_command(his, i + 1)) != NULL) {
                    interpret_command(str, his, c);
                    str = next;
                } else {
                    delete_command(his, i);
                    break;
                }
            }
            return UNDO;
        }
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
        case UNDO:
            return "undo!";
        case UNKNOWN:
            return "error: unknown command";
        case ERRNONINT:
            return "Non-int value is included";
        case ERRLACKARGS:
            return "Too few arguments";
        case NOCOMMAND:
            return "No command in history";
    }
    return NULL;
}
