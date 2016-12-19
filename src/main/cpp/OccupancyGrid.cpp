#include "OccupancyGrid.hpp"
#include <unordered_set>
#include <unordered_map>
#include <cstddef>

using std::unordered_set;
using std::unordered_map;


OccupancyGrid::OccupancyGrid(const vector<Point4>& points,
                             float x_min, float x_max, float x_num,
                             float y_min, float y_max, float y_num,
                             float z_min, float z_max, float z_num,
                             float w_min, float w_max, float w_num,
                             float w_scale) :
                             points(points),
                             x_min(x_min), x_max(x_max), x_num(x_num),
                             y_min(y_min), y_max(y_max), y_num(y_num),
                             z_min(z_min), z_max(z_max), z_num(z_num),
                             w_min(w_min), w_max(w_max), w_num(w_num),
                             w_scale(w_scale) {}

float OccupancyGrid::get_increment(float start, float end, float num) {
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
                                     float num,
                                     float coordinate) {
  float increment = get_increment(start, end, num);
  float offset = get_offset(coordinate, start);
  int index = get_index(offset, increment);
  return get_center(index, increment, start);
}

vector<Point4> OccupancyGrid::get_grid() {
  unordered_map<Point4,uint8_t> center_point_map;
  vector<Point4>::iterator point_it = points.begin();
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
    float w_center = round_to_center(this->w_min,
                                     this->w_max,
                                     this->w_num,
                                     point_it->w);
    w_center = w_center * w_scale;
    center_point_map[Point4{ x_center,y_center,z_center,w_center }]++;
  }
  vector<Point4> center_point_vector;
  auto center_it = center_point_map.begin();
  for (; center_it != center_point_map.end(); center_it++) {
    //if (center_it->second >= 2) center_point_vector.push_back(center_it->first);
    center_point_vector.push_back(center_it->first);
  }
  return center_point_vector;
}
