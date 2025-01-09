#include "traverse.h"

#include <stdio.h>

void traverse(const Node *n) {
    if (n == NULL) return;

    printf("value = %d\n", n->value);
    traverse(n->left);
    traverse(n->right);
}

void traverse_inorder(const Node *n) {
    if (n == NULL) return;

    traverse_inorder(n->left);
    printf("value = %d\n", n->value);
    traverse_inorder(n->right);
}

void traverse_postorder(const Node *n) {
    if (n == NULL) return;

    traverse_postorder(n->left);
    traverse_postorder(n->right);
    printf("value = %d\n", n->value);
}