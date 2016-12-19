#include "Point4.hpp"

bool Point4::operator==(const Point4 &o) const {
  return (x==o.x&&y==o.y&&z==o.z&&w==o.w);
}

bool Point4::operator!=(const Point4 &o) const {
  return !(*this == o);
}