#ifndef TREEMAP_H
#define TREEMAP_H

enum Color{
  RED,
  BLACK
};

typedef struct node{
  char* key;
  void* value;
  enum Color color;
  struct node* left;
  struct node* right;
  struct node* parent;
}Node;

typedef struct tree{
  Node* root;
  Node* NIL;
} Treemap;

Treemap* createTreemap();
Node* createNode(char* key, void* value);

#endif
