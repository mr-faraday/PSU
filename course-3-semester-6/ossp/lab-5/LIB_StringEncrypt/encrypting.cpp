#include "pch.h"
#include "encrypting.h"

#include <string.h>
#include <wchar.h>

void goEncrypt(wchar_t*, wchar_t*);

void encrypt(wchar_t* destStr, int size, const wchar_t* sourceStr) {
  wchar_t* buffer = new wchar_t[MAX_STRING_SIZE];
  memset(buffer, 0, MAX_STRING_SIZE);
  wcscpy_s(buffer, size + 1, sourceStr);

  wchar_t* curr = buffer;
  wchar_t* next = buffer + 1;
  
  goEncrypt(curr, next);
  wcscpy_s(destStr, size + 1, buffer);
  delete[] buffer;
}

void goEncrypt(wchar_t* c, wchar_t* n) {
  if (*n == '\0') {
    return;
  }

  wchar_t b = *c;
  *c = *n;
  *n = b;

  goEncrypt(c + 2, n + 2);
}
