/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Операционые системы и системное программрование
 * Лабораторная №3
 * Задание 1
 * 1) Написать программу-сервер согласно индивидуальному заданию.
 * 2) Написать программу-клиент согласно индивидуальному заданию.
 * 3) Связать работу двух приложений;
 * Приведение слов к общему виду по определенным условиям. На сервер клиент шлет вариант приведения слова, сервер приводи слова к этому виду и обратно отсылает клиенту. Протокол взаимодействия UDP.
 */

// Клиент

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Недостаточно параметров\n");
    exit(1);
  }
  char message[64];
  strcpy(message, argv[1]);
  char buf[sizeof(message)];

  int sock;
  struct sockaddr_in addr;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    perror("socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);  // или любой другой порт...
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    exit(2);
  }
  send(sock, message, sizeof(message), 0);
  recv(sock, buf, sizeof(message), 0);
  printf("%s\n", buf);
  close(sock);

  return 0;
}
