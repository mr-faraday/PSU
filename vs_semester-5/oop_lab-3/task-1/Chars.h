#pragma once

#include <iostream>

const size_t mSize = 2048;

struct Char {
  Char* nextCh = nullptr;
  char value = 0;
};

class Chars {
private:
  Char* listStart;
  size_t maxSize;
  size_t size;
public:
  Chars();
  ~Chars();

  char getCh();
  void print();
  void input();

  Chars& operator+(char ch);
  void operator --();
  bool operator == (char const& ch);
};

