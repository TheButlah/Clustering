#include "include/OccupancyGrid.hpp"
#include <unordered_set>
#include <cstddef>

using std::unordered_set;


OccupancyGrid::OccupancyGrid(const vector<Point3D>& points,
                             double x_min, double x_max, int x_num,
                             double y_min, double y_max, int y_num,
                             double z_min, double z_max, int z_num) :
                             points(points),
                             x_min(x_min), x_max(x_max), x_num(x_num),
                             y_min(y_min), y_max(y_max), y_num(y_num),
                             z_min(z_min), z_max(z_max), z_num(z_num) {}

double OccupancyGrid::get_increment(double start, double end, int num) {
  return (end - start) / num;
}

double OccupancyGrid::get_offset(double coordinate, double start) {
  return coordinate - start;
}

int OccupancyGrid::get_index(double offset, double increment) {
  return (int) (offset / increment);
}

double OccupancyGrid::get_center(int index, double increment, double start) {
  return start + ((index + 0.5) * increment);
}

double OccupancyGrid::round_to_center(double start,
                                      double end,
                                      int num,
                                      double coordinate) {
  double increment = get_increment(start, end, num);
  double offset = get_offset(coordinate, start);
  int index = get_index(offset, increment);
  return get_center(index, increment, start);
}

vector<Point3D> OccupancyGrid::get_grid() {
  unordered_set<Point3D> center_point_set;
  vector<Point3D>::iterator point_it = points.begin();
  for (; point_it < points.end(); point_it++) {
    double x_center = round_to_center(this->x_min,
                                      this->x_max,
                                      this->x_num,
                                      point_it->x);
    double y_center = round_to_center(this->y_min,
                                      this->y_max,
                                      this->y_num,
                                      point_it->y);
    double z_center = round_to_center(this->z_min,
                                      this->z_max,
                                      this->z_num,
                                      point_it->z);
    center_point_set.insert(Point3D{x_center, y_center, z_center});
  }
  vector<Point3D> center_point_vector;
  auto center_it = center_point_set.begin();
  for (; center_it != center_point_set.end(); center_it++) {
    center_point_vector.push_back(*center_it);
  }
  return center_point_vector;
}
