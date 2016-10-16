#include "PointCloud.hpp"

PointCloud::PointCloud(std::vector<Point3D> points) : pts(points) {}

inline size_t PointCloud::kdtree_get_point_count() const { return pts.size(); }


inline double PointCloud::kdtree_distance(const double* p1,
                              const size_t idx_p2,
                              size_t) const {
    const double d0=p1[0]-pts[idx_p2].x;
    const double d1=p1[1]-pts[idx_p2].y;
    const double d2=p1[2]-pts[idx_p2].z;
    return d0*d0+d1*d1+d2*d2;
}

inline double PointCloud::kdtree_get_pt(const size_t idx, int dim) const {
    if (dim==0) return pts[idx].x;
    else if (dim==1) return pts[idx].y;
    else return pts[idx].z;
}

template <class BBOX> bool PointCloud::kdtree_get_bbox(BBOX&) const {return false; }
