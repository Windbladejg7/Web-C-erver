#include "http.h"

void createRouter();
void addGet(char* ruta, handler func);
void route(HttpRequest* req, HttpResponse* res);
