#include "Mask.hpp"

class PartialCircularMask : public Mask {
private:
  vector<Point3> points;
  float radius, degrees;
public:
  PartialCircularMask(const vector<Point3>& points,
                      float radius,
                      float degrees);
  vector<Point3> filter();
};
