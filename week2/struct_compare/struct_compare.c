#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obj.h"

int main() {
    Obj h1 = {.a = 1.0, .b = 'c', .c = 2.0};
    Obj h2 = h1;

    // before trick
    printf("(%f %f)\n", h1.a, h2.a);
    printf("(%f %f)\n", h1.c, h2.c);
    printf("(%c %c)\n", h1.b, h2.b);

    printf("%s\n", (!memcmp(&h1, &h2, sizeof(Obj))) ? "true" : "false");
    printf("%s\n", (!memcmp(&h1.a, &h2.a, sizeof(8))) ? "true" : "false");
    printf("%s\n", (!memcmp(&h1.b, &h2.b, sizeof(8))) ? "true" : "false");
    printf("%s\n", (!memcmp(&h1.c, &h2.c, sizeof(8))) ? "true" : "false");

    printf("%p %p %p\n", &h2.a, &h2.b, &h2.c);
    printf("%zu %zu %zu %zu\n", sizeof(h2), sizeof(h2.a), sizeof(h2.b),
           sizeof(h2.c));

    h2 = trick(h2);  // h2 をいじる

    // after trick
    printf("(%f %f)\n", h1.a, h2.a);
    printf("(%f %f)\n", h1.c, h2.c);
    printf("(%c %c)\n", h1.b, h2.b);

    char *p = &h2.b;
    for (int i = 0; i < 8; ++i) {
        printf("%c ", *(p + i));
    }
    printf("\n");

    printf("%s\n", (!memcmp(&h1, &h2, sizeof(Obj))) ? "true" : "false");
    printf("%s\n", (!memcmp(&h1.a, &h2.a, sizeof(8))) ? "true" : "false");
    printf("%s\n", (!memcmp(&h1.b, &h2.b, sizeof(8))) ? "true" : "false");
    printf("%s\n", (!memcmp(&h1.c, &h2.c, sizeof(8))) ? "true" : "false");

    printf("%p %p %p\n", &h2.a, &h2.b, &h2.c);
    printf("%zu %zu %zu %zu\n", sizeof(h2), sizeof(h2.a), sizeof(h2.b),
           sizeof(h2.c));

    return 0;
}
