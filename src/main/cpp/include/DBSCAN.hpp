#pragma once
#include <vector>
#include "Point3.hpp"
#include "nanoflann.hpp"
#include "PointCloud.hpp"


class DBSCAN {

  public:
    //enum class PointStatus { UNVISITED, NOISE, CLUSTERED };
    DBSCAN(const std::vector<Point3>& points, float epsilon, size_t minPts);
    std::vector< std::vector<Point3> > cluster();

    //inlined because templates in C++ need to be fully defined in headers
    template<class T>
    inline static void merge(std::vector<T>& resultVector,
                             const std::vector<T>& otherVector) {

      remove_copy_if(otherVector.begin(),otherVector.end(),
                     back_inserter(resultVector),
                     [&resultVector](T elt) -> bool {//This is a lambda function
                       return resultVector.end() !=
                         find(resultVector.begin(),resultVector.end(), elt);
                     }
      );
    }

  private:
    //int numPoints;
    //std::vector<Point3> points;
    typedef std::unordered_map<size_t, uint8_t > statusmap_t;

    typedef nanoflann::KDTreeSingleIndexAdaptor<
            nanoflann::L2_Simple_Adaptor<float,PointCloud>,
            PointCloud, 
            3
            > my_kd_tree_t;

    const float eps;
    const size_t minPts;

    const PointCloud cloud;

    my_kd_tree_t tree;
    statusmap_t visited;

    void expandCluster(size_t focalPoint,
                       std::vector<size_t>& cluster,
                       std::vector<size_t>& neighbors);

    std::vector<size_t> getNeighbors(size_t point);
};
