#include "CircularMask.hpp"

CircularMask::CircularMask(const vector<Point3>& points, float radius) :
    points(points), radius(radius) {};

vector<Point3> CircularMask::filter() {
  vector<Point3>::iterator point = this->points.begin();
  vector<Point3> filtered_points;
  float radius_squared = this->radius * this->radius;
  for (; point != points.end(); point++) {
    if ((point->x * point->x + point->y * point->y) <= radius_squared) {
      filtered_points.push_back(*point);
    }
  }
  return filtered_points;
};
