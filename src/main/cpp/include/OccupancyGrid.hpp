#pragma once
#include <vector>
#include <set>
#include "Point3.hpp"

using std::vector;
using std::set;

class OccupancyGrid {
private:
  vector<Point3> points;
  float x_min, y_min, z_min;
  float x_max, y_max, z_max;
  int x_num, y_num, z_num;
  static float get_increment(float start, float end, int num);
  static float get_offset(float coordinate, float start);
  static int get_index(float offset, float increment);
  static float get_center(int index, float increment, float start);
  static float round_to_center(float start,
                               float end,
                               int num,
                               float coordinate);
public:
  OccupancyGrid(const vector<Point3>& points,
                float x_min, float x_max, int x_num,
                float y_min, float y_max, int y_num,
                float z_min, float z_max, int z_num);
  vector<Point3> get_grid();
};
