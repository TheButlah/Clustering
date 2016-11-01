#include "RectangularMask.hpp"

RectangularMask::RectangularMask(vector<Point3>& points,
                                 float x_min,
                                 float x_max,
                                 float y_min,
                                 float y_max) :
                                 points(points),
                                 x_min(x_min),
                                 x_max(x_max),
                                 y_min(y_min),
                                 y_max(y_max) {};

vector<Point3> RectangularMask::filter() {
  vector<Point3>::iterator point = this->points.begin();
  vector<Point3> filtered_points;
  for (; point != this->points.end(); point++) {
    if (point->x >= this->x_min &&
        point->x <= this->x_max &&
        point->y >= this->y_min &&
        point->y <= this->y_max) {
      filtered_points.push_back(*point);
    }
  }
  return filtered_points;
}
