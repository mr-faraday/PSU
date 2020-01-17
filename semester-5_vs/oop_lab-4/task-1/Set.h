#pragma once

#include <iostream>

const int maxSize = 1024;

template<class T>
struct cell {
  cell<T>* next = nullptr;
  T value;
};

template<class T>
class Set {
private:
  cell<T>* arrStart;
  size_t mSize;
  size_t size;
  void insert(const T& value);
  void clear();
public:
  Set();
  ~Set();
  void input();
  void print();
  int Int();
  Set(const Set& ob);
  Set<T>& operator = (const Set<T>& set);
  Set<T>& operator + (const T& value);
  Set<T> operator * (const Set<T>& set);
};

template<class T>
inline void Set<T>::insert(const T& value) {
  // Для пустого массива
  if (this->size == 0) {
    arrStart = new cell<T>;
    arrStart->value = value;

    size++;
    return;
  }

  cell<T>* p;
  p = arrStart;

  while (p != nullptr) {
    // Уже есть
    if (value == p->value) break;
    // Вставить в начало
    if (value < p->value && p == arrStart) {
      arrStart = new cell<T>;
      arrStart->value = value;
      arrStart->next = p;

      size++;
      return;
    }
    // Вставить в конце
    if (value > p->value && p->next == nullptr) {
      p->next = new cell<T>;
      p->next->value = value;

      size++;
      return;
    }
    // Вставить в середине
    if (value < p->value) {
      cell<T>* n = new cell<T>;
      n->value = value;
      n->next = p;
      
      cell<T>* prev_p = arrStart;
      while (prev_p->next != p) prev_p = prev_p->next;
      prev_p->next = n;
      
      size++;
      return;
    }

    p = p->next;
  }
}

template<class T>
inline void Set<T>::clear() {
  if (size == 0) return;
  cell<T>* p = arrStart;
  while (p != nullptr) {
    p = arrStart;
    if (arrStart != nullptr) arrStart = arrStart->next;
    delete p;
  }
  size = 0;
}

template<class T>
inline Set<T>::Set() {
  mSize = maxSize;
  size = 0;
  arrStart = nullptr;
}

template<class T>
inline Set<T>::~Set() {
  cell<T>* p = arrStart;
  while (p != nullptr) {
    p = arrStart;
    if (arrStart != nullptr) arrStart = arrStart->next;
    delete p;
  }
}

template<class T>
inline void Set<T>::input() {
  T value;
  std::wcout << L"Введите значение(ия):" << L"\n\r";
  std::wcin >> value;
  std::wcout << L"\n\r";
  insert(value);
}

template<class T>
inline void Set<T>::print() {
  if (size == 0) return;
  cell<T>* p = arrStart;
  while (p != nullptr) {
    std::wcout << p->value << L"\n\r";
    p = p->next;
  }
  std::wcout << L"\n\r";
}

template<class T>
inline int Set<T>::Int() {
  return size;
}

template<class T>
inline Set<T>::Set(const Set& ob) {
  cell<T>* p = ob.arrStart;
  while (p != nullptr) {
    this->insert(p->value);
    p = p->next;
  }
}

template<class T>
inline Set<T>& Set<T>::operator=(const Set& copySet) {
  if (this == &copySet) return *this;
  clear();
  mSize = copySet.mSize;
  cell<T>* p = copySet.arrStart;
  for (size_t i = 0; i < copySet.size; i++) {
    insert(p->value);
    p = p->next;
  }

  return *this;
}

template<class T>
inline Set<T>& Set<T>::operator+(const T& value) {
  insert(value);

  return *this;
}

template<class T>
inline Set<T> Set<T>::operator*(const Set<T>& set) {
  Set<T> cross;
  cell<T>
    *p1,
    *p2;
  p1 = this->arrStart;
  for (size_t i = 0; i < this->size; i++) {
    //if (p1 == nullptr) break;
    p2 = set.arrStart;
    for (size_t j = 0; j < set.size; j++) {
      //if (p2 == nullptr) break;
      if (p1->value == p2->value) cross.insert(p1->value);
      p2 = p2->next;
    }
    p1 = p1->next;
  }
  
  return cross;
}
