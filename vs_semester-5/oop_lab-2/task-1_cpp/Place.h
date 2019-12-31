#pragma once

#include "City.h"

class Place :
  public City {
private:
  std::wstring placeName;
public:
  Place(std::wstring name);
protected:
  virtual void getInfo();  
};
