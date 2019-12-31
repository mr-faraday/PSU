#include "Laptop.h"

Laptop::Laptop(
  std::wstring mark,
  std::wstring model,
  float CPU_clockRate,
  float GPU_clockRate,
  int RAM_size,
  int GPU_RAM_size
) {
  Laptop::mark = mark;
  Laptop::model = model;
  Laptop::CPU_clockRate = CPU_clockRate;
  Laptop::GPU_clockRate = GPU_clockRate;
  Laptop::RAM_size = RAM_size;
  Laptop::GPU_RAM_size = GPU_RAM_size;
}

Laptop::Laptop(const Laptop& obj) {}

Laptop::~Laptop() {}

std::wstring Laptop::getMark() {
  return mark;
}

std::wstring Laptop::getModel() {
  return model;
}

float Laptop::getCPUcr() {
  return CPU_clockRate;
}

float Laptop::getGPUcr() {
  return GPU_clockRate;
}

int Laptop::getRAMs() {
  return RAM_size;
}

int Laptop::getGPUrs() {
  return GPU_RAM_size;
}

std::wstring Laptop::setMark(std::wstring value) {
  mark = value;
  return value;
}

std::wstring Laptop::setModel(std::wstring value) {
  model = value;
  return value;
}

float Laptop::setCPUcr(float value) {
  CPU_clockRate = value;
  return value;
}

float Laptop::setGPUcr(float value) {
  GPU_clockRate = value;
  return value;
}

int Laptop::setRAMs(int value) {
  RAM_size = value;
  return value;
}

int Laptop::setGPUrs(int value) {
  GPU_RAM_size = value;
  return value;
}

Laptop& Laptop::operator=(const Laptop& ob) {
  this->mark = ob.mark;
  this->model = ob.model;
  this->CPU_clockRate = ob.CPU_clockRate;
  this->GPU_clockRate = ob.GPU_clockRate;
  this->RAM_size = ob.RAM_size;
  this->GPU_RAM_size = ob.GPU_RAM_size;

  return *this;
}

Laptop::Laptop() {
  Laptop::mark = L"Empty";
  Laptop::model = L"Empty";
  Laptop::CPU_clockRate = 0;
  Laptop::GPU_clockRate = 0;
  Laptop::RAM_size = 0;
  Laptop::GPU_RAM_size = 0;
}

bool operator==(const Laptop& ob_l, const Laptop& ob_r) {
  bool b =
    (ob_l.mark == ob_r.mark) &&
    (ob_l.model == ob_r.model) &&
    (ob_l.CPU_clockRate == ob_r.CPU_clockRate) &&
    (ob_l.GPU_clockRate == ob_r.GPU_clockRate) &&
    (ob_l.RAM_size == ob_r.RAM_size) &&
    (ob_l.GPU_RAM_size == ob_r.GPU_RAM_size);
  return b;
}

bool operator!=(const Laptop& ob_l, const Laptop& ob_r) {
  bool b =
    (ob_l.mark != ob_r.mark) &&
    (ob_l.model != ob_r.model) &&
    (ob_l.CPU_clockRate != ob_r.CPU_clockRate) &&
    (ob_l.GPU_clockRate != ob_r.GPU_clockRate) &&
    (ob_l.RAM_size != ob_r.RAM_size) &&
    (ob_l.GPU_RAM_size != ob_r.GPU_RAM_size);
  return b;
}

bool operator>(const Laptop& ob_l, const Laptop& ob_r) {
  bool b;
  if (ob_l.mark > ob_r.mark) b = true;
  else if (ob_l.model > ob_r.model)  b = true;
  else if (ob_l.CPU_clockRate > ob_r.CPU_clockRate)  b = true;
  else if (ob_l.GPU_clockRate > ob_r.GPU_clockRate)  b = true;
  else if (ob_l.RAM_size > ob_r.RAM_size)  b = true;
  else if (ob_l.GPU_RAM_size > ob_r.GPU_RAM_size)  b = true;
  else b = false;

  return b;
}

bool operator<(const Laptop& ob_l, const Laptop& ob_r) {
  bool b;
  if (ob_l.mark < ob_r.mark) b = true;
  else if (ob_l.model < ob_r.model)  b = true;
  else if (ob_l.CPU_clockRate < ob_r.CPU_clockRate)  b = true;
  else if (ob_l.GPU_clockRate < ob_r.GPU_clockRate)  b = true;
  else if (ob_l.RAM_size < ob_r.RAM_size)  b = true;
  else if (ob_l.GPU_RAM_size < ob_r.GPU_RAM_size)  b = true;
  else b = false;

  return b;
}

std::wostream& operator<<(std::wostream& out, const Laptop& ob) {
  out << ob.model << L"\n\r";
  out << ob.mark << L"\n\r";
  out << ob.CPU_clockRate << L"\n\r";
  out << ob.GPU_clockRate << L"\n\r";
  out << ob.RAM_size << L"\n\r";
  out << ob.GPU_RAM_size << L"\n\r";
  out << L"\n\r";

  return out;
}

std::wistream& operator>>(std::wistream& in, Laptop& ob) {
  in >> ob.model;
  in >> ob.mark;
  in >> ob.CPU_clockRate;
  in >> ob.GPU_clockRate;
  in >> ob.RAM_size;
  in >> ob.GPU_RAM_size;

  return in;
}
