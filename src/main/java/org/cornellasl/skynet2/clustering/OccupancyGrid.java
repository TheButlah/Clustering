package org.cornellasl.skynet2.clustering;

import org.cornellasl.skynet2.util.*;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class OccupancyGrid {

  public static Set<Point3D> getOccupancyGrid(List<Point3D> point_list,
                                              double xStart,
                                              double xEnd,
                                              int xNum,
                                              double yStart,
                                              double yEnd,
                                              int yNum,
                                              double zStart,
                                              double zEnd,
                                              int zNum) {

    double starts[] = {xStart, yStart, zStart};
    double ends[] = {xEnd, yEnd, zEnd};
    int nums[] = {xNum, yNum, zNum};
    double increments[] = new double[3];
    for (int i = 0; i < 3; i++) {
      increments[i] = getIncrement(starts[i], ends[i], nums[i]);
    }
    Set<Point3D> centerPointSet = new HashSet<Point3D>();
    for (Point3D point: point_list) {
      double coordinates[] = {point.getX(), point.getY(), point.getZ()};
      double centers[] = new double[3];
      for (int i = 0; i < 3; i++) {
        double offset = getOffset(coordinates[i], starts[i]);
        int index = getIndex(offset, increments[i]);
        centers[i] = getCenter(index, increments[i]);
      }
      Point3D centerPoint = new Point3D(centers[0], centers[1], centers[2]);
      centerPointSet.add(centerPoint);
    }

    return centerPointSet;
  }

  private static double getIncrement(double start, double end, double num) {
    return (start - end) / num;
  }

  private static double getOffset(double coordinate, double start) {
    return coordinate - start;
  }

  private static int getIndex(double offset, double increment) {
    return (int) (offset / increment);
  }

  private static double getCenter(int index, double increment) {
    return (index + 0.5) * increment;
  }

}
