#pragma once

typedef struct node
{
  int value;
  struct node *left;
  struct node *right;
} Node;

// 木のルートを与えて操作する
void traverse(const Node *n);
void traverse_inorder(const Node *n);
void traverse_postorder(const Node *n);
