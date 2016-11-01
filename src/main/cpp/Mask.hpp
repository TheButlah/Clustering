#pragma once

#include <vector>
#include "Point3.hpp"

using std::vector;

class Mask {
private:
  vector<Point3> points;
public:
  virtual vector<Point3> filter() = 0;
};
