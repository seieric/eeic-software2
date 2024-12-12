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

Node *push_front(Node *begin, const char *str) {
  Node *p = (Node *)malloc(sizeof(Node));
  char *s = (char *)malloc(strlen(str) + 1);
  strcpy(s, str);

  *p = (Node){.str = s, .next = begin};

  return p;
}

Node *pop_front(Node *begin) {
  assert(begin != NULL);
  Node *p = begin->next;

  free(begin->str);
  free(begin);

  return p;
}

Node *push_back(Node *begin, const char *str) {
  if (begin == NULL) {
    return push_front(begin, str);
  }

  Node *p = begin;
  while (p->next != NULL) {
    p = p->next;
  }

  Node *q = (Node *)malloc(sizeof(Node));
  char *s = (char *)malloc(strlen(str) + 1);
  strcpy(s, str);

  *q = (Node){.str = s, .next = NULL};
  p->next = q;

  return begin;
}

// Let's try: pop_back の実装
Node *pop_back(Node *begin) {
  assert(begin != NULL);

  Node *node = begin;
  Node *prev = NULL;
  while (node->next != NULL) {
    prev = node;
    node = node->next;
  }

  if (node == begin) {
    begin = NULL;
  } else {
    prev->next = NULL;
  }

  free(node->str);
  free(node);

  return begin;
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

Node *remove_all(Node *begin) {
  while ((begin = pop_front(
              begin)));  // Repeat pop_front() until the list becomes empty
  return begin;
}

int main() {
  Node *begin = NULL;

  char buf[maxlen];
  while (fgets(buf, maxlen, stdin)) {
    begin = push_front(begin, buf);
    if (strcmp("Otsuka\n", buf) == 0) {
      insert(begin, "Sugamo\n");
    }
    // begin = push_back(begin, buf); // Try this instead of push_front()
  }

  // begin = pop_front(begin);  // What will happen if you do this?
  begin = pop_back(begin);   // What will happen if you do this?
  begin = push_back(begin, "Takanawagateway\n");

  // begin = remove_all(begin); // What will happen if you do this?

  for (const Node *p = begin; p != NULL; p = p->next) {
    printf("%s", p->str);
  }

  return EXIT_SUCCESS;
}
