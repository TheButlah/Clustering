package org.cornellasl.skynet2.clustering;

import org.cornellasl.skynet2.clustering.OccupancyGrid;
import org.cornellasl.skynet2.util.CSVReader;
import org.cornellasl.skynet2.util.Point3D;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Test {

  public static void main(String args[]) throws IOException, FileNotFoundException {
    List<Point3D> pointList = CSVReader.read("res/occ.csv");
    FileOutputStream fos;
    PrintWriter pw;

    long start = System.nanoTime();
    Set<Point3D> centerPointSet = OccupancyGrid.getOccupancyGrid(pointList, -120, 120, 960, -100, 100, 800, -20, 20, 160);
    DBSCAN dbscan = new DBSCAN(centerPointSet, 1, 10);
    List<List<Point3D>> clusters = dbscan.cluster();
    long stop = System.nanoTime();

    fos = new FileOutputStream("results/occupancy_grid.csv");
    pw = new PrintWriter(fos);
    for (Point3D centerPoint : centerPointSet) {
      pw.println(centerPoint);
    }
    pw.close();
    fos.close();

    fos = new FileOutputStream("results/clusters_over.csv");
    pw = new PrintWriter(fos);
    int index = 0;
    for (List<Point3D> cluster : clusters) {
      index++;
      for (Point3D point : cluster) {
        pw.println(point + "," + index);
      }
    }
    pw.close();
    fos.close();
    //Set<Point3D> set = new HashSet<>(pointList);

    //System.out.println("numpoints: " + dbscan.);
    System.out.println("numclusters: " + clusters.size());
    for (List<Point3D> cluster : clusters) {
      //System.out.println(cluster.size());
    }
    System.out.println("DBSCAN computation time (s): " + (stop-start)*1E-9);



  }

}
