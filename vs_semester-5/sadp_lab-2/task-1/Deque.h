#pragma once

#include <iostream>

template<typename T>
struct Link {
  Link<T>* next = nullptr;
  Link<T>* prev = nullptr;

  T data;
};

template<class T>
class Deque {
private:
  Link<T>* begin = nullptr;
  Link<T>* end = nullptr;
  size_t size = 0;

public:
  Deque() {}
  ~Deque() {
    clear();
  }

  bool empty() {
    return !(size);
  }
  int clear() {
    Link<T>* p = begin;
    while (begin != nullptr) {
      begin = p->prev;
      delete p;
      p = begin;
    }
    end = nullptr;
    size = 0;

    return 1;
  }
  size_t getSize() {
    return size;
  }
  T pushFront(T data) {
    // Для пустого дека
    if (size == 0) {
      begin = new Link<T>;
      begin->data = data;
      end = begin;

      size++;
      return data;
    }

    Link<T>* n = new Link<T>;
    begin->next = n;
    n->prev = begin;
    begin = n;
    n->data = data;

    size++;
    return data;
  }
  T pushBack(T data) {
    // Для пустого дека
    if (size == 0) {
      end = new Link<T>;
      end->data = data;
      begin = end;

      size++;
      return data;
    }

    Link<T>* n = new Link<T>;
    end->prev = n;
    n->next = end;
    end = n;
    n->data = data;

    size++;
    return data;
  }
  T popFront() {
    if (size == 0) exit(5);
    
    if (size == 1) {
      T d = begin->data;
      this->clear();
      
      return d;
    }

    T d = begin->data;
    begin = begin->prev;
    delete begin->next;
    begin->next = nullptr;

    size--;
    return d;
  }
  T popBack() {
    if (size == 0) exit(5);

    if (size == 1) {
      T d = end->data;
      this->clear();

      return d;
    }

    T d = end->data;
    end = end->next;
    delete end->prev;
    end->prev = nullptr;

    size--;
    return d;
  }
  T getFront() {
    if (size == 0) exit(5);

    return begin->data;
  }
  T getBack() {
    if (size == 0) exit(5);

    return end->data;
  }
};
