#include <iostream>
#include <vector>
#include "include/Point3D.hpp"
#include "DBSCAN.hpp"


using namespace std;

//let PointStatus print its value
std::ostream& operator<<(std::ostream& out, const DBSCAN::PointStatus value) {
  const char *s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
  switch (value) {
    PROCESS_VAL(DBSCAN::PointStatus::UNVISITED);
    PROCESS_VAL(DBSCAN::PointStatus::NOISE);
    PROCESS_VAL(DBSCAN::PointStatus::CLUSTERED);
  }
#undef PROCESS_VAL
  return out << s;
}

int main(int argc, char** argv) {
  vector<Point3D> cluster1{{1.0,2.0,3.0},{4.0,5.0,6.0}};
  vector<Point3D> cluster2{{3.0,2.0,1.0},{1.0,2.0,3.0},{0.0,0.0,0.0}};
  DBSCAN::merge(cluster1,cluster2);
  //std::boolalpha flag sets bool values to be printed as text
  cout << "isPod<Point3D>: " << boolalpha << is_pod<Point3D>::value << endl;
  cout << "merged cluster: " << endl;
  for (auto i : cluster1) {
    cout << i << " ";
  }
  cout << endl;
  //cout << "asdf" << DBSCAN::PointStatus::UNVISITED;
  vector<DBSCAN::PointStatus> vec(3);
  for (DBSCAN::PointStatus elt : vec) {
    cout << elt << endl;
  }

  int herp = 1;
  int& derp = herp;
  cout << "herp: " << herp << endl;
  cout << "derp: " << derp << endl;
  derp = 2;
  cout << "herp: " << herp << endl;
  cout << "derp: " << derp << endl;d

}