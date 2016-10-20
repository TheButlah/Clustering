#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include "include/OccupancyGrid.hpp"
#include "include/DBSCAN.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::size_t;

int main() {
  vector<Point3> points;
  string line;
  ifstream fid ("1modmod.csv");
  if (fid.is_open()) {
    while (getline(fid, line)) {
      string::iterator it = line.begin();
      vector<float> point_floats;
      string buffer = "";
      for (; it != line.end(); it++) {
        if (*it == ',') {
          point_floats.push_back(atof(buffer.c_str()));
          buffer = "";
        } else if (*it != '\n') {
          buffer += *it;
        }
      }
      float x = point_floats.at(0);
      float y = point_floats.at(1);
      float z = atof(buffer.c_str());
      points.push_back(Point3{x, y, z});
    }
    fid.close();
  }
  auto start = std::chrono::high_resolution_clock::now();
  const int CYCLES = 500;
  for (int i=0;i<CYCLES;i++){
    OccupancyGrid occupancy_grid = OccupancyGrid(points,
                                                 -120, 120, 720,
                                                 -100, 100, 600,
                                                 -20, 20, 120);
    vector<Point3> center_points = occupancy_grid.get_grid();
    DBSCAN dbscan(center_points, 1, 20);
    vector<vector<Point3> > clusters = dbscan.cluster();
  }
  auto finish = std::chrono::high_resolution_clock::now();
  /*vector<vector<Point3> >::iterator it = clusters.begin();
  size_t idx = 1;
  for (; it != clusters.end(); it++) {
    vector<Point3> cluster = *it;
    vector<Point3>::iterator inner_it = cluster.begin();
    for (; inner_it != cluster.end(); inner_it++) {
      //Point3 point = *inner_it;
      // cout << point << ", " << idx << endl;
    }
    idx++;
  }*/
  cout << "Average Hz: " << CYCLES/(1e-9 * (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count())) << endl;
  //cout << clusters.size() << endl;
  return 0;
}
