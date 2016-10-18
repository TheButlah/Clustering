#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include "include/OccupancyGrid.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

int main() {
  vector<Point3D> points;
  string line;
  ifstream fid ("1modmod.csv");
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
  OccupancyGrid occupancy_grid = OccupancyGrid(points,
                                               -120.0, 120.0, 960,
                                               -100.0, 100.0, 800,
                                               -20.0, 20.0, 160);
  vector<Point3D> center_points = occupancy_grid.get_grid();
  auto finish = std::chrono::high_resolution_clock::now();
  vector<Point3D>::iterator it = center_points.begin();
  int num = 0;
  for (; it < center_points.end(); it++) {
    num++;
    cout << *it << endl;
  }
  cout << num << endl;
  cout << 1e-9 * (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count()) << endl;
  return 0;
}
