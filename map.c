#include <stdlib.h>
#include "map.h"
#include <string.h>

typedef struct node{
  char* key;
  void* value;
} Node;

typedef struct hashmap{
  int size;
  Node** storage;
} Hashmap;

Hashmap* createHashmap(int capacity){
  Hashmap* map = malloc(sizeof(Hashmap));
  map->size = capacity;
  map->storage = calloc(capacity, sizeof(Node*));
  return map;
}

unsigned long hash(unsigned char *str) {
   unsigned long hash = 5381;
   int c;
   while (c = *str++)
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

void insert(void* map, char* key, void* value ){
    Hashmap* m = (Hashmap *)map;
    int index = (int)(hash((unsigned char*)key) % m->size);
    Node* new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    m->storage[index] = new_node;
}

void* get(void* map, char* key){
  Hashmap* m = (Hashmap *)map;
  int index = (int)(hash((unsigned char*)key) % m->size);
  return m->storage[index]->value;
}

