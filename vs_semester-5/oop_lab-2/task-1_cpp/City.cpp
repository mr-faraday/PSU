#include "City.h"

City::City(std::wstring name) :Metropolis(L"unknown") {
  this->cityName = name;
}

void City::getInfo() {
  std::wcout << this->domainName << L"\n\r";
  std::wcout << this->metropolisName << L"\n\r";
  std::wcout << this->cityName << L"\n\r";
  std::wcout << L"\n\r";
}
