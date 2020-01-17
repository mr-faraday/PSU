// Динамическое позднее связывание

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <dlfcn.h>

int main(int argc, char const *argv[]) {
  void *handle = dlopen("libMyDynamic.so", RTLD_LAZY);
  void(*processing)(char*) = dlsym(handle, "processing");

  if (argc < 2) {
    printf("Недостаточно параметров\n");
    exit(1);
  }
  char str[256] = {'\0'};
  strcpy(str, argv[1]);
  processing(&str[0]);
  dlclose(handle);
  printf("%s\n", str);

  return 0;
}
