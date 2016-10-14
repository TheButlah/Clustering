#pragma once
#include <vector>
#include "Point3D.hpp"

class DBSCAN {
  private:
    enum PointStatus { NOISE, CLUSTERED };    
    int numPoints;
    std::vector<Point3D> points;
    std::unordered_map<Point3D, PointStatus> visited;
    //KDTraa tree;

    const double eps;
    const int minPts;

  public:

};
