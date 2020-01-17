// Многопоточный режим: 2 потока

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
  pthread_t thread;  // Дескриптор потока

  // Распредеоение нагрузки
  int oneThreadLoad = (argc-1) / 2;
  int mainThreadLoad = oneThreadLoad + ((argc-1) % 2);
  int status_addr;

  // Параметры на второй поток
  tArgs parms;
  parms.times = oneThreadLoad;  // Колличество слов для обработки
  parms.argv = argv;  // Передача параетров
  parms.start =  1;  // Начало обработки потоком

  // Параметры первого потока
  tArgs parm;
  parm.times = mainThreadLoad;
  parm.start = oneThreadLoad + 1;
  parm.argv = argv;

  if (pthread_create(&thread, NULL, thread_func, (void*) &parms) != 0) {
    return 1;
  }

  (*thread_func)(&parm);
  pthread_join(thread, (void**)&status_addr);

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
