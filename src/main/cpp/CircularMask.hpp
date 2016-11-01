#include "Mask.hpp"

class CircularMask : public Mask {
private:
  vector<Point3> points;
  float radius;
public:
  CircularMask(const vector<Point3>& points, float radius);
  vector<Point3> filter();
};
