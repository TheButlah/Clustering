#pragma once
#include <vector>
#include <set>
#include <memory>

#include "Point4.hpp"

using std::vector;
using std::set;

class OccupancyGrid {
public:

  /**
  * Constructs an OccupancyGrid.
  * The grid takes two points and constructs an occupancy grid
  * with the provided number of cells on each axis. This grid
  * is not restricted to lie within the bounding box formed by the
  * two provided points, as it can accept any input coordinates.
  */
  OccupancyGrid(const vector<Point4>& points,
    float x_min, float x_max, float x_num,
    float y_min, float y_max, float y_num,
    float z_min, float z_max, float z_num,
    float w_min, float w_max, float w_num,
    float w_scale);

  /**
  * Computes the occupancy grid and returns its contents.
  */
  vector<Point4> get_grid();
private:
  vector<Point4> points;
  float x_min, y_min, z_min, w_min;
  float x_max, y_max, z_max, w_max;
  float x_num, y_num, z_num, w_num;
  float w_scale;
  static float get_increment(float start, float end, float num);
  static float get_offset(float coordinate, float start);
  static int get_index(float offset, float increment);
  static float get_center(int index, float increment, float start);
  static float round_to_center(float start,
                               float end,
                               float num,
                               float coordinate);
};
