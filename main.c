#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "router.h"
#include "http.h"

#define PORT_NUMBER 8080
#define BUFFER_SIZE 8192

HttpRequest* parseHttp(char* data){
  HttpRequest* req = malloc(sizeof(HttpRequest));
  req->method =  strtok(data, " ");
  req->uri = strtok(NULL, " ");
  return req;
}
  
void* handle_request(void* fd_pointer){
  char buffer[BUFFER_SIZE];
  int fd = (int)(long)fd_pointer;

  while(1){
    memset(buffer, 0, BUFFER_SIZE);
    int bytesRecibidos = recv(fd, buffer, BUFFER_SIZE, 0);
    if(bytesRecibidos > 0){
      HttpRequest* req = parseHttp(buffer);
      printf("Method: %s\n\n", req->method);
      printf("Uri: %s\n", req->uri);
      HttpResponse* res = malloc(sizeof(HttpResponse));
      route(req, res);
      
      //TODO: Refactorizar esto
      if(res->body == NULL){
        break;
      }

      char sendBuffer[1024];
      int len = sprintf(sendBuffer, 
        "HTTP/1.1 %d %s\r\n"
        "Content-Length: %ld\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "%s", 
        res->statusCode, res->message, res->bodySize, res->body);
      send(fd, sendBuffer, len, 0);
      free(req);
      free(res);
    }else if(bytesRecibidos == 0){
      printf("Cliente desconectado\n");
      break;
    }else{
      printf("Error en recv");
      break;
    }
  }
  close(fd);
  return NULL;  
}

void hello(HttpRequest* req, HttpResponse* res){
  printf("%s - Hello World\n", req->method);
  res->statusCode = 200;
  res->body = (unsigned char*)"Hello desde mi servidor web :)\n";
  res->bodySize = strlen((char*)res->body);
  res->message = "OK";
} 

int main(){
  struct sockaddr_in addr; 

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  
  if(fd < 0){
    printf("Error al crear el socket\n");
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT_NUMBER);
  addr.sin_addr.s_addr = INADDR_ANY;
  memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

  if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    printf("Error en el bind\n");
    return 1;
  }
  
  listen(fd, 10);
  
  printf("Servidor escuchando en el puerto: %d\n", PORT_NUMBER);
  
  createRouter();
  addGet("/hola", hello);
  addGet("/", hello);

  while(1){
    struct sockaddr_in their_addr;
    socklen_t size = sizeof(their_addr);
    int client_fd = accept(fd, (struct sockaddr *)&their_addr, &size);

    if(client_fd < 0){
      printf("Error en accept");
      return 1;
    }
    
    pthread_t id_hilo;

    pthread_create(&id_hilo, NULL, handle_request, (void *)(long)client_fd);
    printf("%d", (int)id_hilo);
    char ip_cliente[16];
    inet_ntop(AF_INET, &(their_addr.sin_addr), ip_cliente, 16); 
    printf("Direccion del cliente: %s\n", ip_cliente);
  } 
}




