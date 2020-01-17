#include "Domain.h"

Domain* Domain::lastObj() {
  Domain* last = Domain::listStart;
  while (last->nextObj != nullptr) last = last->nextObj;

  return last;
}

Domain::Domain(std::wstring domainName) {
  this->domainName = domainName;
  
  if (Domain::listStart) lastObj()->nextObj = this;
  else Domain::listStart = this;
}

void Domain::showList() {
  Domain* obj = Domain::listStart;
  while (obj != nullptr) {
    obj->getInfo();
    obj = obj->nextObj;
  } 
}

void Domain::getInfo() {
  std::wcout << this->domainName << L"\n\r";
  std::wcout << L"\n\r";
}
