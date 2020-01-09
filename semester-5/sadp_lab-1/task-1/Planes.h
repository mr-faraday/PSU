#pragma once
#define UINT unsigned int

#include <iostream>
#include <string>
#include <cmath>

struct Plane {
  Plane* prev = nullptr;
  Plane* next = nullptr;

  UINT serialNum;
  std::wstring mark_model;
  UINT year;
  UINT flyTime;
};

class Planes {
private:
  Plane* listStart = nullptr;
  size_t size = 0;

  int input(const std::wstring&);
  void insert(Plane*);
  Plane* deleteRec(Plane*);
public:
  Planes();
  ~Planes();
  void planesFilter(UINT);
  void printList();
};

