// Сервер

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void processing(char*);

int main(int argc, char const *argv[]) {
  int sock, listener;
  struct sockaddr_in addr;
  char buf[1024];
  int bytes_read;
  listener = socket(AF_INET, SOCK_STREAM, 0);
  if(listener < 0) {
    perror("socket");
    exit(1);
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(2);
  }
  listen(listener, 1);
  while(1) {
    sock = accept(listener, NULL, NULL);
    if (sock < 0) {
      perror("accept");
      exit(3);
    }
    while(1) {
      bytes_read = recv(sock, buf, 1024, 0);
      if(bytes_read <= 0) break;
      processing(&buf[0]);
      send(sock, buf, bytes_read, 0);
    }
  close(sock);
  }

  return 0;
}

void processing(char* c) {
  while (*c != '\0') {
    *c = tolower(*c);
    c++;
  }
}
