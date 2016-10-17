#include "include/DBSCAN.hpp"

using namespace std;

DBSCAN::DBSCAN(vector<Point3D> points, double epsilon, int minPts) :
  eps(epsilon), minPts(minPts), cloud(PointCloud(points)),
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {}


void DBSCAN::merge(vector<Point3D>& resultVector,
                   vector<Point3D>& otherVector) {

  remove_copy_if(otherVector.begin(),otherVector.end(),
                 back_inserter(resultVector),
                 //This is a lambda function
                 [&resultVector](Point3D p) -> bool {
                    return resultVector.end() !=
                      find(resultVector.begin(),resultVector.end(), p);

                 }
  );
}


