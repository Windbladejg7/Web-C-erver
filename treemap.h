#ifndef TREEMAP_H
#define TREEMAP_H

typedef struct node{
  char* key;
  void* value;
  struct node* left;
  struct node* right;
} Node;

typedef struct treemap{
  Node* root;
} Treemap;

Treemap* createTreemap();
Node* createNode(char* key, void* value);
#endif
