#include "radixtreemap.h"
#include "map.h"
#include "router.h"

RadixTree* map;

void createRouter(){
  map = createRadixTree();
  insert(map, "GET", createRadixTree());
}

void addGet(char* ruta, handler func){
  RadixTree* mapGet = (RadixTree *)get(map, "GET");
  insert(mapGet, ruta, func);
}

void route(HttpRequest* req, HttpResponse* res){
  RadixTree* m = (RadixTree *)get(map, req->method);
  handler func = (handler)get(m, req->uri);
  if(func != NULL){
    func(req, res);
  }else{
    printf("ruta no existe\n");
  }
}



