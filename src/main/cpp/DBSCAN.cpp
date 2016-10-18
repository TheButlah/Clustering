#include "include/DBSCAN.hpp"
#define UNVISITED 0
#define NOISE 1
#define CLUSTERED 2

using namespace std;

DBSCAN::DBSCAN(const vector<Point3>& points, float epsilon, size_t minPts) :
  eps(epsilon), minPts(minPts), cloud(PointCloud{points}),
  tree(3,cloud,nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
  tree.buildIndex();
}

vector< vector<Point3> > DBSCAN::cluster() {
  vector< vector<size_t> > clusters;

  for (size_t i = 0; i<cloud.pts.size(); i++) {
    //Holds a reference to the pointStatus in the vector,
    //can directly assign things to this variable and it will work
    uint8_t& status = visited[i];

    if (status != UNVISITED) continue;

    //Detect nearest neighbors based on eps value
    vector<size_t> neighbors = getNeighbors(i);

    if (neighbors.size()<minPts) {
      //Density not high enough, this is noise (can change later though)
      status = NOISE;
    } else {
      //Its a core point, mark it
      status = CLUSTERED;
      vector<size_t> newCluster;
      expandCluster(i,newCluster,neighbors);
      clusters.push_back(newCluster);
    }
    i++;
  }
  vector< vector<Point3> > result(clusters.size());
  size_t idx = 0;
  for (auto cluster = clusters.begin(); cluster != clusters.end(); cluster++) {
    result[idx].reserve(cluster->size());
    size_t idy=0;
    for (auto point = cluster->begin(); point!=cluster->end();point++) {
      result[idx][idy] = cloud.pts[*point];
      idy++;
    }
    idx++;
  }
  return result;
}

/**
 * IMPORTANT: Mutates the neighbors vector, recommend no using it after this
 */
void DBSCAN::expandCluster(size_t focalPoint, std::vector<size_t>& cluster,
                           std::vector<size_t>& neighbors) {
  cluster.push_back(focalPoint);
  //auto it = neighbors.begin();
  size_t i = 0;
  while (i < neighbors.size()) {
    size_t currentPoint = neighbors[i];
    //Holds a reference to the pointStatus in the vector,
    //can directly assign things to this variable and it will work
    uint8_t& pointStatus = visited[currentPoint];
    if (pointStatus == UNVISITED) {
      vector<size_t> newNeighbors = getNeighbors(currentPoint);
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



vector<size_t> DBSCAN::getNeighbors(size_t point) {
  //pairs of pointindex, L2_Squared distance
  vector< pair<size_t,float> > pairs;
  const Point3 point3 = cloud.pts[point];
  const float query_pt[3] = {point3.x,point3.y,point3.z};
  tree.radiusSearch(query_pt,eps,pairs,nanoflann::SearchParams());
  vector<size_t> neighbors(pairs.size());
  for (auto pair : pairs) {
    neighbors.push_back(pair.first);
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
