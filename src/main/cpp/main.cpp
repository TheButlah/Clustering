#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include "OccupancyGrid.hpp"
#include "DBSCAN.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::size_t;

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Incorrect number of arguments!" << endl;
    return 1;
  }
  char* filename = argv[1];
  vector<Point4> points;
  string line;
  ifstream fid(filename);
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
      float z = point_floats.at(2);
      float w = atof(buffer.c_str());
      points.push_back(Point4{x,y,z,w});
    }
    fid.close();
  }
  float radiusSquared = .1;
  int minPts = 32;
  float intensityScale = 1.0/60.0;

  float x_min = -5;
	float x_max = 50;
  float cellsPerX = 8;

  float y_min = -6;
	float y_max = 9;
  float cellsPerY = 16;

  float z_min = -4;
  float z_max = 4
  float cellsPerZ = 8;

  float w_min = 0;
  float w_max = 255;
  float cellsPerW = 16;


  auto start = std::chrono::high_resolution_clock::now();
  RectangularMask rectangular_mask(points, x_min, x_max, y_min, y_max);
	vector<Point4> masked_points = rectangular_mask.filter();

	OccupancyGrid occupancy_grid = OccupancyGrid(masked_points,
		x_min, x_max, (x_max - x_min) * cellsPerX,
		y_min, y_max, (y_max - y_min) * cellsPerY,
		z_min, z_max, (z_max - z_min) * cellsPerZ,
    w_min, w_max, (w_max - w_min) * cellsPerW,
    intensityScale);
	vector<Point4> center_points = occupancy_grid.get_grid();
  DBSCAN dbscan(center_points, radiusSquared, minPts);
  vector<vector<Point4> > clusters = dbscan.cluster();
  auto finish = std::chrono::high_resolution_clock::now();
  cout << "Number of Points in Pointcloud: " << points.size() << endl;
  cout << "Number of Points after Masking: " << masked_points.size() << endl;
  cout << "Number of Points in Occupancy Grid: " << center_points.size() << endl;
  cout << "Number of Clusters: " << clusters.size() << endl;
  cout << "Computation Time: " << 1e-9 * (std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count()) << endl;
  vector<vector<Point4> >::iterator it = clusters.begin();
  size_t idx = 1;
  for (; it != clusters.end(); it++) {
    vector<Point4> cluster = *it;
    vector<Point4>::iterator inner_it = cluster.begin();
    for (; inner_it != cluster.end(); inner_it++) {
      //Point4 point = *inner_it;
      // cout << point << ", " << idx << endl;
    }
    idx++;
  }
  return 0;
}
