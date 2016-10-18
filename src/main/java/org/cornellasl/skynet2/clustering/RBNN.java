package org.cornellasl.skynet2.clustering;

import org.cornellasl.skynet2.util.*;

import java.util.*;

public class RBNN {

  public static List<List<Point3D>> getClusters(Set<Point3D> centerPoints,
                                                double threshold) {
    return null;
  }

  public static List<Point3D> mergeClusters(List<Point3D> cluster1,
                                            List<Point3D> cluster2) {
    Collection<Point3D> mergedCluster = new HashSet<>();
    mergedCluster.addAll(cluster1);
    mergedCluster.addAll(cluster2);
    return new ArrayList<Point3D>(mergedCluster);
  }
}
