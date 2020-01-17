// Многопоточный режим: 4 потока

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

typedef struct thread_Args {
  char const **argv;
  int times;
  int start;
} tArgs;

void *thread_func(void *argsT);

int main(int argc, char const *argv[]) {
  pthread_t thread[3];  // Дескрипторы потоков

  // Распредеоение нагрузки
  int oneThreadLoad = (argc-1) / 4;
  int mainThreadLoad = oneThreadLoad + ((argc-1) % 4);
  int status_addr;

  // Параметры на каждый поток
  tArgs parms[3];
  for (int i = 0; i < 3; i++) {
    parms[i].times = oneThreadLoad;  // Колличество слов для обработки
    parms[i].argv = argv;  // Передача параетров
    parms[i].start =  i*oneThreadLoad + 1;  // Начало обработки потоком
  }

  for (int i = 0; i < 3; i++) {
    if (pthread_create(&thread[i], NULL, thread_func, (void*) &parms[i]) != 0) {
      return 1;
    }
  }

  tArgs parm;
  parm.times = mainThreadLoad;
  parm.start = 3*oneThreadLoad + 1;
  parm.argv = argv;
  (*thread_func)(&parm);


  pthread_join(thread[0], (void**)&status_addr);
  pthread_join(thread[1], (void**)&status_addr);
  pthread_join(thread[2], (void**)&status_addr);

  return 0;
}

void *thread_func(void *argsT) {
  tArgs *args = (tArgs*) argsT;

  char str[128] = {'\0'};
  char* c;
  for (int i = args->start ; i < (args->times + args->start); i++) {
    memset(str, 0, sizeof(str));  // очистка
    strcpy(str, args->argv[i]);  // копирование строк
    c = str;
    while (*c != '\0') {
      *c = tolower(*c);  // В lowercase
      c++;
    }
    printf("%s\n", str);
  }

  return 0;
}
