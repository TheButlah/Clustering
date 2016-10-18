#pragma once
#include <iostream>
#include <cstddef>
#include <unordered_map>

struct Point3 {
  float x,y,z;

  bool operator==(const Point3 &o) const;

  bool operator!=(const Point3 &o) const;

};

//Defined outside struct because otherwise implicit [this] breaks it
inline std::ostream& operator<<(std::ostream& out, const Point3& p){
  return out << p.x << ", " << p.y << ", " << p.z;
}

//This code adds hashing functionality for Point3 to std::hash
namespace std {
    template <>
    struct hash<Point3> {
        std::size_t operator()(const Point3& k) const {
            // std::cout << "hashing a Point3d!";
            std::size_t res = 17;
            res = res * 31 + std::hash<float>()( k.x );
            res = res * 31 + std::hash<float>()( k.y );
            return res * 31 + std::hash<float>()( k.z );
        }
    };
}
