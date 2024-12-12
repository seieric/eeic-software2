#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxlen = 1000;

typedef struct node Node;

struct node {
  char *str;
  Node *next;
};

typedef struct list {
  Node *begin;
} List;

List *push_front(List *list, const char *str) {
  Node *p = (Node *)malloc(sizeof(Node));
  char *s = (char *)malloc(strlen(str) + 1);
  strcpy(s, str);

  *p = (Node){.str = s, .next = list->begin};

  list->begin = p;

  return list;
}

List *pop_front(List *list) {
  assert(list->begin != NULL);
  Node *p = list->begin->next;

  free(list->begin->str);
  free(list->begin);

  list->begin = p;

  return list;
}

List *push_back(List *list, const char *str) {
  if (list->begin == NULL) {
    return push_front(list, str);
  }

  Node *p = list->begin;
  while (p->next != NULL) {
    p = p->next;
  }

  Node *q = (Node *)malloc(sizeof(Node));
  char *s = (char *)malloc(strlen(str) + 1);
  strcpy(s, str);

  *q = (Node){.str = s, .next = NULL};
  p->next = q;

  return list;
}

// Let's try: pop_back の実装
List *pop_back(List *list) {
  assert(list->begin != NULL);

  Node *begin = list->begin;
  Node *node = begin;
  Node *prev = NULL;
  while (node->next != NULL) {
    prev = node;
    node = node->next;
  }

  if (node == begin) {
    list->begin = NULL;
  } else {
    prev->next = NULL;
  }

  free(node->str);
  free(node);

  return list;
}

Node *insert(Node *p, const char *str) {
  if (p == NULL) return p;

  Node *new = (Node *)malloc(sizeof(Node));
  char *s = (char *)malloc(strlen(str) + 1);
  strcpy(s, str);

  *new = (Node){.next = p->next, .str = s};
  p->next = new;

  return new;
}

List *remove_all(List *list) {
  while ((list = pop_front(
              list)));  // Repeat pop_front() until the list becomes empty
  list->begin = NULL;
  return list;
}

int main() {
  List _list = {.begin = NULL};
  List *list = &_list;

  char buf[maxlen];
  while (fgets(buf, maxlen, stdin)) {
    list = push_front(list, buf);
    if (strcmp("Otsuka\n", buf) == 0) {
      insert(list->begin, "Sugamo\n");
    }
    // begin = push_back(begin, buf); // Try this instead of push_front()
  }

  // begin = pop_front(begin);  // What will happen if you do this?
  list = pop_back(list);  // What will happen if you do this?
  list = push_back(list, "Takanawagateway\n");

  // begin = remove_all(begin); // What will happen if you do this?

  for (const Node *p = list->begin; p != NULL; p = p->next) {
    printf("%s", p->str);
  }

  return EXIT_SUCCESS;
}
