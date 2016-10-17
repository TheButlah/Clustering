#pragma once
#include <vector>
#include "Point3D.hpp"
#include "nanoflann.hpp"
#include "PointCloud.hpp"


class DBSCAN {
  private:

    enum PointStatus { NOISE, CLUSTERED };
    //int numPoints;
    //std::vector<Point3D> points;
    typedef std::unordered_map<Point3D, PointStatus> statusmap_t;
    statusmap_t visited;
    
    //typedef int my_kd_tree_t;
    typedef nanoflann::KDTreeSingleIndexAdaptor<
            nanoflann::L2_Simple_Adaptor<double,PointCloud>, 
            PointCloud, 
            3
            > my_kd_tree_t;


    const double eps;
    const int minPts;

    const PointCloud cloud;

    my_kd_tree_t tree;

    void expandCluster(Point3D focalPoint,
                       const std::vector<Point3D>& cluster,
                       const std::vector<Point3D>& neighbors);

    std::vector<Point3D> getNeighbors(const Point3D& point);


  public:
    DBSCAN(std::vector<Point3D> points, double epsilon, int minPts);
    std::vector< std::vector<Point3D> > cluster();
    static void merge(std::vector<Point3D>& resultVector,
                      std::vector<Point3D>& otherVector);
};
