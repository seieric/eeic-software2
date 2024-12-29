#pragma once
#include <stdio.h>

typedef struct history History;

void save_history(const char *filename, History *his);

void *push_command(History *his, const char *str);

History *init_history(size_t bufsize);

size_t get_bufsize(History *his);

char *get_command(History *his, int i);
void delete_command(History *his, int i);