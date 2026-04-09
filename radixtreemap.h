#ifndef RADIXTREEMAP_H
#define RADIXTREEMAP_H

#include "list.h"
#include <stdbool.h>

typedef struct node{
  char* prefix;
  void* value;
  ArrayList* children;
  bool isTerminal;
}Node;

typedef struct radix{
  Node* root;
}RadixTree;

Node* createNode(char* prefix, void* value, bool isTerminal);
RadixTree* createRadixTree();

#endif
