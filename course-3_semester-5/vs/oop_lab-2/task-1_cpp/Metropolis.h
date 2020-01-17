#pragma once

#include "Domain.h"

class Metropolis :
  public Domain {
private:
public:
  Metropolis(std::wstring name);
protected:
  virtual void getInfo();
  std::wstring metropolisName;
};
