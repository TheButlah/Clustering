#include "Mask.hpp"

class RectangularMask : public Mask {
private:
  vector<Point4> points;
  float x_min, x_max, y_min, y_max;
public:
  RectangularMask(vector<Point4>& points,
                  float x_min,
                  float x_max,
                  float y_min,
                  float y_max);
  vector<Point4> filter();
};
