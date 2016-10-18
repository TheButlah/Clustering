#pragma once
#include <iostream>
#include <cstddef>
#include <unordered_map>

struct Point3D {
  double x,y,z;

  bool operator==(const Point3D &o) const;

  bool operator!=(const Point3D &o) const;

};

//Defined outside struct because otherwise implicit [this] breaks it
inline std::ostream& operator<<(std::ostream& out, const Point3D& p){
  return out << p.x << ", " << p.y << ", " << p.z;
}

//This code adds hashing functionality for Point3D to std::hash
namespace std {
    template <>
    struct hash<Point3D> {
        std::size_t operator()(const Point3D& k) const {
            // std::cout << "hashing a Point3d!";
            std::size_t res = 17;
            res = res * 31 + std::hash<double>()( k.x );
            res = res * 31 + std::hash<double>()( k.y );
            return res * 31 + std::hash<double>()( k.z );
        }
    };
}
