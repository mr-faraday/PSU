#pragma once

#include <string>
#include <iostream>

class Domain {
private:
  Domain* lastObj();
  Domain* nextObj = nullptr;
public:
  Domain(std::wstring domainName);
  static void showList();
  static Domain* listStart;
protected:
  virtual void getInfo();
  std::wstring domainName;
};
