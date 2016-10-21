#pragma once
#include <vector>
#include "Point3.hpp"
#include <memory>

class DBSCAN {

  public:
    /**
     * Constructs a DBSCAN object.
     * This internally processes [points] so that the clustering algorithm
     * can run much more quickly. It is separate from the [cluster()] method
     * to allow the user to do this preprocessing separately from [cluster()],
     * however in typical applications, [cluster()] is likely to be invoked
     * immediately following this.
     *
     * @param points    The pointcloud to cluster.
     * @param epsilon   The squared euclidian radius within which to expand a cluster
     * @param minPts    The minimum points that must lie in the search radius to expand
     *                  the cluster.
     * @return          An instance of the DBSCAN object
     */
    DBSCAN(const std::vector<Point3>& points, float epsilon, size_t minPts);
    ~DBSCAN();


    /**
     * Clusters the points.
     * Typically invoked right after constructing a DBSCAN object
     * @return A vector of clusters, each of which is a vector of points.
     */
    std::vector< std::vector<Point3> > cluster();

    /**
     * Merge two vectors.
     * Will not merge elements of [otherVector] into [resultVector] if they
     * already exist in [resultVector]. This means that if [resultVector] has
     * no duplicate entries, then merging [otherVector] into it will result in
     * a vector with unique elements.
     *
     * @param resultVector The vector to collect the merged results
     * @param otherVector The vector to merge into [resultVector]
     */
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



  public:
    class Impl;
    std::unique_ptr<Impl> impl;
};
