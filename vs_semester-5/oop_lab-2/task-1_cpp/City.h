#pragma once

#include "Metropolis.h"

class City :
  public Metropolis {
private:
public:
  City(std::wstring name);
protected:
  virtual void getInfo();
  std::wstring cityName;
};
