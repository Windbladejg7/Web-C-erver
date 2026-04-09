typedef struct array{
  void** elements;
  int capacity;
  int length;
}ArrayList;

ArrayList* createArrayList(int size);
void* getAt(ArrayList* list, int index);
void resize(ArrayList* list);
void insertAt(ArrayList* list, int index, void* value);
void push(ArrayList* list, void* value);

