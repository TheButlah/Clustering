#include "include/DBSCAN.hpp"

using namespace std;

DBSCAN::DBSCAN(vector<Point3D> points, double epsilon, int minPts) :
  eps(epsilon), minPts(minPts), cloud(PointCloud{points}),
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
  tree.buildIndex();
}


/*vector<Point3D> DBSCAN::getNeighbors(const Point3D& point) {
  vector<Point3D> neighbors = tree.r
}*/


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


