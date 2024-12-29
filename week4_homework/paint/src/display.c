#include <stdio.h>

void rewind_screen(unsigned int line) { printf("\e[%dA", line); }

void clear_command(void) { printf("\e[2K"); }

void clear_screen(void) { printf("\e[2J"); }