#include "util.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_int(const char *argvalue) {
    long nl;
    char *e;
    errno = 0;  // errno.h で定義されているグローバル変数を一旦初期化
    nl = strtol(argvalue, &e, 10);
    if (errno == ERANGE) {
        fprintf(stderr, "%s: %s\n", argvalue, strerror(errno));
        exit(1);
    }
    if (*e != '\0') {
        fprintf(stderr, "%s: an irregular character '%c' is detected.\n",
                argvalue, *e);
        exit(1);
    }
    return (int)nl;
}

double load_double(const char *argvalue) {
    double ret;
    char *e;
    errno = 0;  // errno.h で定義されているグローバル変数を一旦初期化
    ret = strtod(argvalue, &e);
    if (errno == ERANGE) {
        fprintf(stderr, "%s: %s\n", argvalue, strerror(errno));
        exit(1);
    }
    if (*e != '\0') {
        fprintf(stderr, "%s: an irregular character '%c' is detected.\n",
                argvalue, *e);
        exit(1);
    }
    return ret;
}
