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

    std::vector<size_t> getNeighbors(const Point3D& point);


  public:
    DBSCAN(const std::vector<Point3D>& points, double epsilon, int minPts);
    std::vector< std::vector<Point3D> > cluster();

    //inlined because templates in C++ need to be fully defined in headers
    template<class T>
    inline static void merge(std::vector<T>& resultVector,
                      std::vector<T>& otherVector) {

      remove_copy_if(otherVector.begin(),otherVector.end(),
                     back_inserter(resultVector),
                     //This is a lambda function
                     [&resultVector](T elt) -> bool {
                         return resultVector.end() !=
                                find(resultVector.begin(),resultVector.end(), elt);

                     }
      );
    }
};
