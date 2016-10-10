package org.cornellasl.skynet2.clustering;

import org.cornellasl.skynet2.util.KDTree;
import org.cornellasl.skynet2.util.Point3D;

import java.util.*;
import java.util.List;

public class DBSCAN {

  private int numPoints;
  private List<Point3D> points;
  private HashMap<Point3D, PointStatus> visited;
  private KDTree<Point3D> tree;

  private double eps;
  private int minPts;

  /**
   * NOTE: Do not modify points once passed to constructor
   * @param points Set of points, in order to enforce uniqueness of all points
   * @param epsilon The epsilon value - squared L2 norm between clusters,
   *                must be >=0
   * @param minPts The minimum number of points required to expand a cluster,
   *               must be >=1
   */
  public DBSCAN(Set<Point3D> points, double epsilon, int minPts) {

    this.eps = epsilon;
    this.minPts = minPts;

    this.points = new ArrayList<>(points);
    this.numPoints = points.size();
    this.visited = new HashMap<>();
    //Init K-D tree with 3 dimensions (x,y,z)
    this.tree = new KDTree<>(3);
    //Populate K-D tree
    for (Point3D point : points) {
      //K-D tree has keys as array style coordinates, and values as Point3D
      tree.add(point.getPointArray(),point);
    }
  }

  /**
   * Cluster the points using DBSCAN clustering algorithm
   * Some inspiration taken from apache's ml library
   * @return A List of clusters
   */
  public List<List<Point3D>> cluster() {
    List<List<Point3D>> clusters = new ArrayList<>();
    for (Point3D point : points) {

      //Skip visited points
      if (visited.get(point) != null) continue;
      //visited.add(point);

      //Detect nearest neighbors based on eps
      List<Point3D> neighbors = getNeighbors(point);

      //Density not high enough, this is noise (although it could change later)
      if (neighbors.size() < minPts) {
        visited.put(point, PointStatus.NOISE);
      } else {
        visited.put(point, PointStatus.CLUSTERED);
        clusters.add(expandCluster(point, new ArrayList<Point3D>(), neighbors));
      }
    }
    return clusters;
  }

  private List<Point3D> expandCluster(Point3D focalPoint, List<Point3D> cluster,
                             List<Point3D> neighbors) {
    cluster.add(focalPoint);

    int index = 0;
    while (index < neighbors.size()) {
      Point3D currentPoint = neighbors.get(index);
      PointStatus pointStatus = visited.get(currentPoint);
      //Is nonvisited
      if (pointStatus == null) {
        List<Point3D> newNeighbors = getNeighbors(currentPoint);
        if (newNeighbors.size() >= minPts) {
          neighbors = merge(neighbors,newNeighbors);
        }
        //Otherwise, dont add the new neighbors
      }

      //If is not clustered (will be visited, may not be in visited map yet)
      if (pointStatus != PointStatus.CLUSTERED) {
        visited.put(currentPoint, PointStatus.CLUSTERED);
        cluster.add(currentPoint);
      }

      index++;
    }

    return cluster;


  }

  private List<Point3D> getNeighbors(Point3D point) {
    //construct bounding box centered on point, with l,w,h of 2*eps
    double[] min = point.getPointArray();
    for (int i=0;i<min.length;i++) min[i]=min[i]-eps;
    double[] max = point.getPointArray();
    for (int i=0;i<min.length;i++) min[i]=min[i]+eps;

    //Get points within that bounding box to weed out most points
    List<Point3D> neighbors = new ArrayList<>(tree.getRange(min,max));

    //Use iterator instead of foreach because iter.remove() is more efficient
    //than doing neighbors.remove(neighbor)
    Iterator<Point3D> iter = neighbors.iterator();
    while (iter.hasNext()) {
      Point3D neighbor = iter.next();
      //Check NNs using L2 norms instead of bounding box for increased accuracy
      if (neighbor.getDistanceSquared(point) > eps) iter.remove();
    }
    //Add center point because I'm unsure if its included in the tree.getRange()
    if (!neighbors.contains(point)) neighbors.add(point);
    return neighbors;
  }

  private static <T> List<T> merge(final List<T> c1, final List<T> c2) {
    final Set<T> mergedCollection = new HashSet<>(c1);
    mergedCollection.addAll(c2);
    return new ArrayList<T>(mergedCollection);
  }

  private enum PointStatus {
    NOISE, CLUSTERED
  }
}
