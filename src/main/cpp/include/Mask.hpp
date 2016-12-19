#pragma once

#include <vector>
#include "Point4.hpp"

using std::vector;

class Mask {
private:
  vector<Point4> points;
public:
  virtual vector<Point4> filter() = 0;
};
