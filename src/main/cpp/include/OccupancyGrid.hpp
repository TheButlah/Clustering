#pragma once
#include <vector>
#include <set>
#include "Point3.hpp"

using std::vector;
using std::set;

class OccupancyGrid {
private:
  vector<Point3> points;
  double x_min, y_min, z_min;
  double x_max, y_max, z_max;
  int x_num, y_num, z_num;
  static double get_increment(double start, double end, int num);
  static double get_offset(double coordinate, double start);
  static int get_index(double offset, double increment);
  static double get_center(int index, double increment, double start);
  static double round_to_center(double start,
                                double end,
                                int num,
                                double coordinate);
public:
  OccupancyGrid(const vector<Point3>& points,
                double x_min, double x_max, int x_num,
                double y_min, double y_max, int y_num,
                double z_min, double z_max, int z_num);
  vector<Point3> get_grid();
};
