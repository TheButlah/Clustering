#include "include/Point3D.hpp"

bool Point3D::operator==(const Point3D &o) const {
  return (x==o.x&&y==o.y&&z==o.z);
}

bool Point3D::operator!=(const Point3D &o) const {
  return !(*this == o);
}

