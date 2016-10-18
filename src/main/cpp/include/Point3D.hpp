#pragma once
#include <iostream>
#include <cstddef>
#include <unordered_map>

struct Point3D {
  // Coordinates of point (in meters)
  double x,y,z;

  // Overwriting == operator for Point3Ds
  bool operator==(const Point3D &o) const;

  // Overwriting != operator for Point3Ds
  bool operator!=(const Point3D &o) const;

  // Hash function operator struct for use in unordered_set
  struct Hash {
    std::size_t operator()(const Point3D& point) const {
      std::size_t res = 17;
      res = res * 31 + std::hash<double>()( point.x );
      res = res * 31 + std::hash<double>()( point.y );
      return res * 31 + std::hash<double>()( point.z );
    }
  };

};

// Overwriting << operator for printing
// Defined outside struct because otherwise implicit [this] breaks it
inline std::ostream& operator<<(std::ostream& out, const Point3D& p){
  return out << p.x << ", " << p.y << ", " << p.z;
}
