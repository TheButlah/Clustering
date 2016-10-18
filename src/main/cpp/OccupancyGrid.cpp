#include "include/OccupancyGrid.hpp"
#include <unordered_set>
#include <cstddef>

using std::unordered_set;


OccupancyGrid::OccupancyGrid(const vector<Point3>& points,
                             float x_min, float x_max, int x_num,
                             float y_min, float y_max, int y_num,
                             float z_min, float z_max, int z_num) :
                             points(points),
                             x_min(x_min), x_max(x_max), x_num(x_num),
                             y_min(y_min), y_max(y_max), y_num(y_num),
                             z_min(z_min), z_max(z_max), z_num(z_num) {}

float OccupancyGrid::get_increment(float start, float end, int num) {
  return (end - start) / num;
}

float OccupancyGrid::get_offset(float coordinate, float start) {
  return coordinate - start;
}

int OccupancyGrid::get_index(float offset, float increment) {
  return (int) (offset / increment);
}

float OccupancyGrid::get_center(int index, float increment, float start) {
  return start + ((index + 0.5) * increment);
}

float OccupancyGrid::round_to_center(float start,
                                      float end,
                                      int num,
                                      float coordinate) {
  float increment = get_increment(start, end, num);
  float offset = get_offset(coordinate, start);
  int index = get_index(offset, increment);
  return get_center(index, increment, start);
}

vector<Point3> OccupancyGrid::get_grid() {
  unordered_set<Point3> center_point_set;
  vector<Point3>::iterator point_it = points.begin();
  for (; point_it < points.end(); point_it++) {
    float x_center = round_to_center(this->x_min,
                                      this->x_max,
                                      this->x_num,
                                      point_it->x);
    float y_center = round_to_center(this->y_min,
                                      this->y_max,
                                      this->y_num,
                                      point_it->y);
    float z_center = round_to_center(this->z_min,
                                      this->z_max,
                                      this->z_num,
                                      point_it->z);
    center_point_set.insert(Point3{x_center, y_center, z_center});
  }
  vector<Point3> center_point_vector;
  auto center_it = center_point_set.begin();
  for (; center_it != center_point_set.end(); center_it++) {
    center_point_vector.push_back(*center_it);
  }
  return center_point_vector;
}
