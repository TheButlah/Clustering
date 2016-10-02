package org.cornellasl.skynet2;

import java.io.FileNotFoundException;
import java.io.IOException;

import org.cornellasl.skynet2.clustering.OccupancyGrid;
import org.cornellasl.skynet2.util.*;

import java.util.List;
import java.util.Set;

public class Test {

  public static void main(String args[]) throws FileNotFoundException,
                                                IOException {
    List<Point3D> pointList = CSVReader.read("test.csv");
    Set<Point3D> centerPointSet = OccupancyGrid.getOccupancyGrid(pointList, 0.0, 2.5, 3, 0.0, 2.5, 3, 0.0, 2.5, 3);
    for (Point3D point: centerPointSet) {
      System.out.println(point);
    }
  }

}
