#pragma once
#include <vector>
#include <set>
#include "Point3D.hpp"
#include "include/nanoflann.hpp"


class DBSCAN {
  private:
    struct PointCloud {
      std::vector<Point3D> pts;

      inline size_t kdtree_get_point_count() const { return pts.size(); }


      inline double kdtree_distance(const double* p1, 
                                    const size_t idx_p2, 
                                    size_t) const {
        const double d0=p1[0]-pts[idx_p2].x;
        const double d1=p1[1]-pts[idx_p2].y;
        const double d2=p1[2]-pts[idx_p2].z;
        return d0*d0+d1*d1+d2*d2;
      }

      inline double kdtree_get_pt(const size_t idx, int dim) const {
        if (dim==0) return pts[idx].x;
        else if (dim==1) return pts[idx].y;
        else return pts[idx].z;
      }

      template <class BBOX> bool kdtree_get_bbox(BBOX&) const {return false; }
    };


    enum PointStatus { NOISE, CLUSTERED };    
    int numPoints;
    std::vector<Point3D> points;
    typedef std::unordered_map<Point3D, PointStatus> statusmap_t;
    statusmap_t visited;
    
    typedef int my_kd_tree_t;
    /*typedef nanoflann::KDTreeSingleIndexAdaptor<
            nanoflann::L2_Simple_Adaptor<double,PointCloud>, 
            PointCloud, 
            3
            > my_kd_tree_t;*/
    my_kd_tree_t tree;

    const double eps;
    const int minPts;

    void expandCluster(Point3D focalPoint,
                       const std::vector<Point3D>& cluster,
                       const std::vector<Point3D>& neighbors);

    std::vector<Point3D> getNeighbors(Point3D point);

    static std::vector<Point3D> merge(const std::vector<Point3D>& one,
                                      const std::vector<Point3D>& two);


  public:
    DBSCAN(std::vector<Point3D> points, double epsilon, int minPts);
    std::vector< std::vector<Point3D> > cluster();
};
