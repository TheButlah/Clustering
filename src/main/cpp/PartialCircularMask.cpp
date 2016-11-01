#include <cmath>
#include "PartialCircularMask.hpp"

using std::atan2;

PartialCircularMask::PartialCircularMask(const vector<Point3>& points,
                                         float radius,
                                         float degrees) :
                                         points(points),
                                         radius(radius),
                                         degrees(degrees) {};

vector<Point3> PartialCircularMask::filter() {
  vector<Point3>::iterator point = this->points.begin();
  vector<Point3> filtered_points;
  float radius_squared = this->radius * this->radius;
  float lower_angle = this->degrees * M_PI / 180;
  float upper_angle = (180 - this->degrees) * M_PI / 180;
  for (; point != this->points.end(); point++) {
    float angle = atan2(point->y, point->x);
    if ((point->x * point->x + point->y * point->y <= radius_squared) &&
        (angle >= lower_angle) &&
        (angle <= upper_angle)) {
      filtered_points.push_back(*point);
    }
  }
  return filtered_points;
}
