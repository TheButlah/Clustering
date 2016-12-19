#pragma once
#include <iostream>
#include <cstddef>
#include <unordered_map>
#include "Point3.hpp"

struct Point4 {
  float x, y, z, w;

  bool operator==(const Point4 &o) const;

  bool operator!=(const Point4 &o) const;

};

//Defined outside struct because otherwise implicit [this] breaks it
inline std::ostream& operator<<(std::ostream& out, const Point4& p) {
  return out << p.x << ", " << p.y << ", " << p.z << ", " << p.w;
}

//This code adds hashing functionality for Point4 to std::hash
namespace std {
  template <>
  struct hash<Point4> {
    std::size_t operator()(const Point4& k) const {
      std::hash<float> hasher;
      std::size_t res = hasher(k.x);
      res ^= hasher(k.y) + 0x9e3779b9 + (res << 6) + (res >> 2);
      res ^= hasher(k.z) + 0x9e3779b9 + (res << 6) + (res >> 2);
      res ^= hasher(k.w) + 0x9e3779b9 + (res << 6) + (res >> 2);
      return res;
    }
  };
}
