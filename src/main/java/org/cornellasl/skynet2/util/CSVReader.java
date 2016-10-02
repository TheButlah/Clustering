package org.cornellasl.skynet2.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.io.IOException;

import java.util.ArrayList;
import java.util.List;

/**
 * Class for reading CSV of (X, Y, Z) coordinate information. CSV should not
 * have a header.
 */
public class CSVReader {

  /**
   * Generate a list of Point3Ds from CSV File object
   * @param  file CSV File object
   * @return      List of Point3Ds
   * @throws      FileNotFoundException, IOException
   */
  private static List<Point3D> read(File file) throws FileNotFoundException,
                                                      IOException {

    // Initialize List of Point3Ds
    List<Point3D> pointList = new ArrayList<Point3D>();

    // Create BufferedReader to read CSV file lines
    FileInputStream fileInputStream = new FileInputStream(file);
    InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream);
    BufferedReader bufferedReader = new BufferedReader(inputStreamReader);

    // Read line
    String line = bufferedReader.readLine();

    // While not end of file...
    while (line != null) {

      // Split line by commas
      String lineArray[] = line.split(",");

      // Parse each element as a double
      double coordinateArray[] = new double[3];
      for (int i = 0; i < 3; i++) {
        coordinateArray[i] = Double.parseDouble(lineArray[i]);
      }
      double x = coordinateArray[0];
      double y = coordinateArray[1];
      double z = coordinateArray[2];

      // Create and add corresponding Point3D
      Point3D point = new Point3D(x, y, z);
      pointList.add(point);

      // Read line
      line = bufferedReader.readLine();
    }

    // Close reader and stream
    bufferedReader.close();
    inputStreamReader.close();
    fileInputStream.close();

    return pointList;
  }

  /**
   * Generate a list of Point3Ds from CSV filename String
   * @param  filename CSV file relative path
   * @return          List of Point3Ds
   * @throws          FileNotFoundException, IOException
   */
  public static List<Point3D> read(String filename) throws FileNotFoundException,
                                                           IOException {

    // Create File object from filename
    File file = new File(filename);

    // Read File object
    return read(file);
  }

}
