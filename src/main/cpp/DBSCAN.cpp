#include "include/DBSCAN.hpp"
#define UNVISITED 0
#define NOISE 1
#define CLUSTERED 2

using namespace std;

DBSCAN::DBSCAN(const vector<Point3>& points, double epsilon, int minPts) :
  eps(epsilon), minPts((size_t) minPts), cloud(PointCloud{points}),
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
  tree.buildIndex();
}

vector< vector<Point3> > DBSCAN::cluster() {
  vector< vector<Point3> > clusters;
  for (const Point3& point : cloud.pts) {
    //Holds a reference to the pointStatus in the vector,
    //can directly assign things to this variable and it will work
    uint8_t& status = visited[point];

    if (status != UNVISITED) continue;

    //Detect nearest neighbors based on eps value
    vector<Point3> neighbors = getNeighbors(point);

    if (neighbors.size()<minPts) {
      //Density not high enough, this is noise (can change later though)
      status = NOISE;
    } else {
      //Its a core point, mark it
      status = CLUSTERED;
      vector<Point3> newCluster;
      expandCluster(point,newCluster,neighbors);
      clusters.push_back(newCluster);
    }
  }
  return clusters;
}

/**
 * IMPORTANT: Mutates the neighbors vector, recommend no using it after this
 */
void DBSCAN::expandCluster(Point3 focalPoint, std::vector<Point3>& cluster,
                           std::vector<Point3>& neighbors) {
  cluster.push_back(focalPoint);
  //auto it = neighbors.begin();
  size_t i = 0;
  while (i < neighbors.size()) {
    Point3 currentPoint = neighbors[i];
    //Holds a reference to the pointStatus in the vector,
    //can directly assign things to this variable and it will work
    uint8_t& pointStatus = visited[currentPoint];
    if (pointStatus == UNVISITED) {
      vector<Point3> newNeighbors = getNeighbors(currentPoint);
      if (newNeighbors.size() >= minPts) {
        merge(neighbors,newNeighbors);
      }
      //Otherwise, dont add the new neighbors
    }

    //These points are visited, but might still be flagged as UNVISITED
    if (pointStatus != CLUSTERED) {
      pointStatus = CLUSTERED;
      cluster.push_back(currentPoint);
    }

    //increment iterator, use this instead of it++ to be generic
    //advance(it,1);
    i++;
  }

}



vector<Point3> DBSCAN::getNeighbors(Point3 point) {
  //pairs of pointindex, L2_Squared distance
  vector< pair<size_t,float> > pairs;
  const auto query_pt[3] = {point.x,point.y,point.z};
  tree.radiusSearch(query_pt,eps,pairs,nanoflann::SearchParams());
  vector<Point3> neighbors(pairs.size());
  for (auto pair : pairs) {
    neighbors.push_back(cloud.pts[pair.first]);
  }
  // cout << neighbors.size() << endl;
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
