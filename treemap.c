#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef TreeNode Node;

Treemap* createTreemap(){
  Treemap* map = malloc(sizeof(Treemap));
  return map;
}

static Node* createNode(char* key, void* value){
  Node* new_node = malloc(sizeof(Node));
  new_node->key = strdup(key);
  new_node->value = value;
  return new_node;
}

void treemapInsert(void* map, char* key, void* value){
  Treemap* m = (Treemap *)map;

  if(m->root == NULL){
    m->root = createNode(key, value);
  }
  
  Node *prev, *current;
  prev = NULL;
  current = m->root;

  while(current != NULL){
    if(strcmp(key, current->key) == 0){
      current->value = value;
    }

    if(strcmp(key, current->key) < 0){
      prev = current;
      current = current->left;
    }else{
      prev = current;
      current = current->left;
    }
  }

  if(strcmp(key, prev->key) < 0){
    prev->left = createNode(key, value);
  }else{
    prev->right = createNode(key, value);
  }
}

void* treemapGet(void* map, char* key){
  Treemap* m = (Treemap *)map;
  Node* current = m->root;

  while(current!=NULL){
    if(strcmp(key, current->key) == 0){
      return current->value;
    }else if(strcmp(key, current->key) < 0){
      current = current->left;
    }else{
      current = current->right;
    }
  }
  return NULL;
}





