// Библиотека

#include <ctype.h>
#include <stdio.h>

extern void processing(char* c) {
  while (*c != '\0') {
    *c = tolower(*c);
    c++;
  }
}
