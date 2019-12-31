#pragma once

#include <string>
#include <iostream>

class Laptop {
public:
  // Свойтва объектов
  std::wstring
    mark,
    model;
  float
    CPU_clockRate,
    GPU_clockRate;
  int
    RAM_size,
    GPU_RAM_size;

public:
    // Конструктор без параметров
  Laptop();

    // Конструктор с параметрами
  Laptop(
    std::wstring mark,
    std::wstring model,
    float CPU_clockRate,
    float GPU_clockRate,
    int RAM_size,
    int GPU_RAM_size
  );

    // Конструктор копирования
  Laptop(const Laptop & obj);

    // Деструктор
  ~Laptop();

    // Получение значений
  std::wstring getMark();
  std::wstring getModel();
  float getCPUcr();
  float getGPUcr();
  int getRAMs();
  int getGPUrs();

    // Установка значений
  std::wstring setMark(std::wstring value);
  std::wstring setModel(std::wstring value);
  float setCPUcr(float value);
  float setGPUcr(float value);
  int setRAMs(int value);
  int setGPUrs(int value);

  // Для 4-го задания 
  Laptop& operator = (const Laptop& copy);
  friend bool operator == (const Laptop& ob_l, const Laptop& ob_r);
  friend bool operator != (const Laptop& ob_l, const Laptop& ob_r);
  friend bool operator > (const Laptop& ob_l, const Laptop& ob_r);
  friend bool operator < (const Laptop& ob_l, const Laptop& ob_r);
  friend std::wostream& operator << (std::wostream& out, const Laptop& ob);
  friend std::wistream& operator >> (std::wistream& in, Laptop& ob);
};
