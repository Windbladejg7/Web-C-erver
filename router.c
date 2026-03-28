#include "treemap.h"
#include "map.h"
#include "router.h"

Treemap* map;

void createRouter(){
  map = createTreemap();
  insert(map, "GET", createTreemap());
}

void addGet(char* ruta, handler func){
  Treemap* mapGet = (Treemap *)get(map, "GET");
  insert(mapGet, ruta, func);
  printf("ruta: %s\n", ruta);
}

void route(HttpRequest* req, HttpResponse* res){
  Treemap* m = (Treemap *)get(map, req->method);
  handler func = (handler)get(m, req->uri);
  if(func != NULL){
    func(req, res);
  }else{
    printf("ruta no existe\n");
  }
}



