#include "Chars.h"

Chars::Chars() {
  this->maxSize = mSize;
  this->size = 0;
}

Chars::~Chars() {
  Char* p = this->listStart;
  while (p != nullptr) {
    p = this->listStart;
    if (this->listStart != nullptr) this->listStart = this->listStart->nextCh;
    delete p;
  }
}

char Chars::getCh() {
  return  this->listStart->value;
}

void Chars::print() {
  std::wcout << getCh() << L"\n\r";
}

void Chars::input() {
  char ch;
  std::wcout << L"Введите символ" << L"\n\r";
  std::cin >> ch;
  *this + ch;
}

Chars& Chars::operator+(char ch) {
  if (size == maxSize) return *this;
  Char* p = new Char;
  p->value = ch;
  p->nextCh = listStart;
  listStart = p;

  size++;
  return *this;
}

void Chars::operator--() {
  if (size == 0) return;
  if (size == 1) {
    delete listStart;
    listStart = nullptr;
    size--;
    return;
  }
  Char* p = listStart;
  listStart = listStart->nextCh;
  delete p;
  size--;
}

bool Chars::operator==(char const& ch) {
  return ch == listStart->value;
}
