#include "DBSCAN.hpp"

DBSCAN::DBSCAN(std::vector<Point3D> points, double epsilon, int minPts) :
  eps(epsilon), minPts(minPts), cloud(PointCloud(points)), 
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {}



