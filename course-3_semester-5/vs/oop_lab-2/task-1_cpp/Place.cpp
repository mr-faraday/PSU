#include "Place.h"

Place::Place(std::wstring name) :City(L"unknown") {
  this->placeName = name;
}

void Place::getInfo() {
  std::wcout << this->domainName << L"\n\r";
  std::wcout << this->metropolisName << L"\n\r";
  std::wcout << this->cityName << L"\n\r";
  std::wcout << this->placeName << L"\n\r";
  std::wcout << L"\n\r";
}
