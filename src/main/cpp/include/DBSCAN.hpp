#pragma once
#include <vector>
#include "Point3.hpp"
#include <memory>
//#include "../nanoflann.hpp"
//#include "../PointCloud.hpp"

class DBSCAN {

  public:
    //enum class PointStatus { UNVISITED, NOISE, CLUSTERED };
    DBSCAN(const std::vector<Point3>& points, float epsilon, size_t minPts);
    ~DBSCAN();

    std::vector< std::vector<Point3> > cluster();

    template<class T>
    inline static void merge(std::vector<T>& resultVector,
               const std::vector<T>& otherVector) {
      remove_copy_if(otherVector.begin(),otherVector.end(),
                     back_inserter(resultVector),
        //This is a lambda function
                     [&resultVector](T elt) -> bool {
                         return resultVector.end() !=
                                find(resultVector.begin(), resultVector.end(), elt);

                     });
    }



  private:
    class Impl;
    std::unique_ptr<Impl> impl;
};
