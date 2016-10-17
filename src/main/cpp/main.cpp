#include <iostream>
#include "DBSCAN.hpp"

using namespace std;

int main(int argc, char** argv) {
  vector<Point3D> cluster1{{1.0,2.0,3.0},{4.0,5.0,6.0}};
  vector<Point3D> cluster2{{3.0,2.0,1.0},{1.0,2.0,3.0},{0.0,0.0,0.0}};
  DBSCAN::merge(cluster1,cluster2);
  cout << is_pod<Point3D>::value << endl;
  for (auto i : cluster1) {
    cout << i << " ";
  }
  cout << endl;
}
