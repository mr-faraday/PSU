#include "Metropolis.h"

Metropolis::Metropolis(std::wstring name):Domain(L"unknown") {
  this->metropolisName = name;
}

void Metropolis::getInfo() {
  std::wcout << this->domainName << L"\n\r";
  std::wcout << this->metropolisName << L"\n\r";
  std::wcout << L"\n\r";
}
