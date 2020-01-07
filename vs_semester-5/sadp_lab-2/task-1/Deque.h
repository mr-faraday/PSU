#pragma once

#include <iostream>

template<typename T>
struct Elem {
  Elem<T>* next = nullptr;
  Elem<T>* prev = nullptr;
  int err = 0;

  T value;
};

template<class T>
class Deque {
private:
  Elem<T>* begin = nullptr;
  Elem<T>* end = nullptr;
  size_t size = 0;
public:
  Deque();
  ~Deque();
  int clear();
  size_t getSize();
  T pushFront(T);
  T pushBack(T);
  Elem<T> popFront();
  Elem<T> popBack();
  Elem<T> getFront();
  Elem<T> getBack();
};

template<class T>
inline Deque<T>::Deque() {}

template<class T>
inline Deque<T>::~Deque() {
  clear();
}

template<class T>
inline int Deque<T>::clear() {
  Elem<T>* p = begin;
  while (begin != nullptr) {
    begin = p->next;
    delete p;
    p = begin;
  }
  end = nullptr;

  size = 0;
  return 1;
}

template<class T>
inline size_t Deque<T>::getSize() {
  return size;
}

template<class T>
inline T Deque<T>::pushFront(T value) {
  // Для пустого дека
  if (size == 0) {
    begin = new Elem<T>;
    begin->value = value;
    end = begin;

    size++;
    return value;
  }

  begin->next = new Elem<T>;
  begin->next->prev = begin;
  begin = begin->next;
  begin->value = value;

  size++;
  return value;
}

template<class T>
inline T Deque<T>::pushBack(T value) {
  // Для пустого дека
  if (size == 0) {
    end = new Elem<T>;
    end->value = value;
    begin = end;

    size++;
    return value;
  }

  end->next = new Elem<T>;
  end->next->prev = end;
  end = end->next;
  end->value = value;

  size++;
  return value;
}

template<class T>
inline Elem<T> Deque<T>::popFront() {
  if (size == 0) {
    Elem<T> e;
    e.err = -1;
    return e;
  }

  Elem<T> v = *begin;
  if (size == 1) {
    clear();

    return v;
  }
  
  begin = begin->prev;
  delete begin->next;
  begin->next = nullptr;

  size--;
  return v;
}

template<class T>
inline Elem<T> Deque<T>::popBack() {
  if (size == 0) {
    Elem<T> e;
    e.err = -1;
    return e;
  }

  Elem<T> v = *end;
  if (size == 1) {
    clear();

    return v;
  }

  end = end->prev;
  delete end->next;
  end->next = nullptr;

  size--;
  return v;
}

template<class T>
inline Elem<T> Deque<T>::getFront() {
  if (size == 0) {
    Elem<T> e;
    e.err = -1;
    return e;
  }

  return *begin;
}

template<class T>
inline Elem<T> Deque<T>::getBack() {
  if (size == 0) {
    Elem<T> e;
    e.err = -1;
    return e;
  }

  return *end;
}
