#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include "include/DBSCAN.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::size_t;

int main() {
  vector<Point3D> points;
  string line;
  ifstream fid ("occ.csv");
  if (fid.is_open()) {
    while (getline(fid, line)) {
      string::iterator it = line.begin();
      vector<double> point_doubles;
      string buffer = "";
      for (; it != line.end(); it++) {
        if (*it == ',') {
          point_doubles.push_back(atof(buffer.c_str()));
          buffer = "";
        } else if (*it != '\n') {
          buffer += *it;
        }
      }
      double x = point_doubles.at(0);
      double y = point_doubles.at(1);
      double z = atof(buffer.c_str());
      points.push_back(Point3D{x, y, z});
    }
    fid.close();
  }
  auto start = std::chrono::high_resolution_clock::now();
  DBSCAN dbscan(points, 2, 10);
  vector<vector<Point3D> > clusters = dbscan.cluster();
  auto finish = std::chrono::high_resolution_clock::now();
  vector<vector<Point3D> >::iterator it = clusters.begin();
  size_t idx = 0;
  for (; it != clusters.end(); it++) {
    vector<Point3D> cluster = *it;
    vector<Point3D>::iterator inner_it = cluster.begin();
    for (; inner_it != cluster.end(); inner_it++) {
      Point3D point = *inner_it;
      // cout << point << ", " << idx << endl;
    }
    idx++;
  }
  cout << 1e-9 * (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count()) << endl;
  return 0;
}
