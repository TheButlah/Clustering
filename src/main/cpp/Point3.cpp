#include "Point3.hpp"

bool Point3::operator==(const Point3 &o) const {
  return (x==o.x&&y==o.y&&z==o.z);
}

bool Point3::operator!=(const Point3 &o) const {
  return !(*this == o);
}