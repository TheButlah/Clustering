#pragma once

#include "Point3.hpp"
#include <vector>

struct PointCloud {
  const std::vector<Point3>& pts;

  inline size_t kdtree_get_point_count() const {
    return pts.size();
  }


  inline float kdtree_distance(const float* p1,
                                const size_t idx_p2,
                                size_t) const {
    const float d0=p1[0]-pts[idx_p2].x;
    const float d1=p1[1]-pts[idx_p2].y;
    const float d2=p1[2]-pts[idx_p2].z;
    return d0*d0+d1*d1+d2*d2;
  }

  inline float kdtree_get_pt(const size_t idx, int dim) const {
    if (dim==0) return pts[idx].x;
    else if (dim==1) return pts[idx].y;
    else return pts[idx].z;
  }

  template <class BBOX> inline bool kdtree_get_bbox(BBOX&) const {
    return false;
  }

};