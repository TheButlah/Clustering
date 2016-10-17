#pragma once

#include "Point3D.hpp"
#include <vector>

struct PointCloud {
    std::vector<Point3D> pts;

    PointCloud(std::vector<Point3D> points);

    size_t kdtree_get_point_count() const;


    double kdtree_distance(const double* p1,
                                  const size_t idx_p2,
                                  size_t) const;

    double kdtree_get_pt(const size_t idx, int dim) const;

    template <class BBOX> bool kdtree_get_bbox(BBOX&) const;
};