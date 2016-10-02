package org.cornellasl.skynet2.util;

import org.junit.Test;

import java.io.IOException;
import java.util.List;

import static org.junit.Assert.*;

public class CSVReaderTest {

  @Test
  public void testRead() {
    String filename = "test.csv";
    List<Point3D> points;
    try {
      points = CSVReader.read(filename);
      System.out.println("hello");
    } catch (IOException e) {
      fail(e.getMessage());
    }

  }

}