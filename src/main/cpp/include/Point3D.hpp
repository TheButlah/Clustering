#pragma once
#include <iostream>
#include <cstddef>
#include <unordered_map>

struct Point3D {
    double x,y,z;

    bool operator==(const Point3D &o) const;

    bool operator!=(const Point3D &o) const;
};
