#include "include/DBSCAN.hpp"


using namespace std;

DBSCAN::DBSCAN(const vector<Point3D>& points, double epsilon, int minPts) :
  eps(epsilon), minPts(minPts), cloud(PointCloud{points}),
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
  tree.buildIndex();
}

vector< vector<Point3D> > DBSCAN::cluster() {
  vector< vector<Point3D> > clusters;
  for (const Point3D& point : cloud.pts) {
    //Holds a reference to the pointStatus in the vector,
    //can directly assign things to this variable and it will work
    PointStatus& status = visited[point];

    if (status != PointStatus::UNVISITED) continue;

    //Detect nearest neighbors based on eps value
    vector<Point3D> neighbors = getNeighbors(point);

    if (neighbors.size()<minPts) {
      //Density not high enough, this is noise (can change later though)
      status = PointStatus::NOISE;
    } else {
      //Its a core point
      status = PointStatus::CLUSTERED;
      vector<Point3D> newCluster;
      expandCluster(point,newCluster,neighbors);
      clusters.push_back(newCluster);
    }
  }
  return clusters;
}



vector<Point3D> DBSCAN::getNeighbors(Point3D point) {
  //pairs of pointindex, L2_Squared distance
  vector< pair<size_t,double> > pairs;
  const double query_pt[3] = {point.x,point.y,point.z};
  tree.radiusSearch(query_pt,eps,pairs,nanoflann::SearchParams());
  vector<Point3D> neighbors(pairs.size());
  for (auto pair : pairs) {
    neighbors.push_back(cloud.pts[pair.first]);
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


