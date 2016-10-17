#include "include/DBSCAN.hpp"



using namespace std;

DBSCAN::DBSCAN(const vector<Point3D>& points, double epsilon, int minPts) :
  eps(epsilon), minPts(minPts), cloud(PointCloud{points}),
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
  tree.buildIndex();
}

vector<size_t> DBSCAN::getNeighbors(const Point3D& point) {
  //pairs of pointindex, L2_Squared distance
  vector<pair<size_t,double>> pairs;
  const double query_pt[3] = {point.x,point.y,point.z};
  tree.radiusSearch(query_pt,eps,pairs,nanoflann::SearchParams());
  vector<size_t> neighbors(pairs.size());
  for (auto pair : pairs) {
    neighbors.push_back(pair.first);
  }
  return neighbors;
}

/*template<class T>
void DBSCAN::merge(vector<T>& resultVector,
                   vector<T>& otherVector) {

  remove_copy_if(otherVector.begin(),otherVector.end(),
                 back_inserter(resultVector),
                 //This is a lambda function
                 [&resultVector](T elt) -> bool {
                    return resultVector.end() !=
                      find(resultVector.begin(),resultVector.end(), elt);

                 }
  );
}*/


