package org.cornellasl.skynet2.util;

/**
 * Class describing pseudo-immutable point in 3D space with double precision
 */
public final class Point3D {

  // Cartesian coordinates x, y, z
  private final double x, y, z;
  //Cache the hashcode
  private int hash = 0;

  /**
   * Create a Point3D object with coordinates x, y, z, specified as doubles
   * @param x x-coordinate
   * @param y y-coordinate
   * @param z z-coordinate
   */
  public Point3D(double x, double y, double z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  /**
   * Create a new array of doubles that represents this Point3D
   * @return This point as an array of doubles
   */
  public double[] getPointArray() {
    double[] tmp =new double[3];
    tmp[0] = x;
    tmp[1] = y;
    tmp[2] = z;
    return tmp;
  }


  /**
   * x-coordinate getter
   * @return x-coordinate double
   */
  public double getX() { return this.x; }

  /**
   * y-coordinate getter
   * @return y-coordinate double
   */
  public double getY() { return this.y; }

  /**
   * z-coordinate getter
   * @return z-coordinate double
   */
  public double getZ() { return this.z; }

  /**
   * Compute the 2-norm distance squared to another Point3D
   * @param  point Another Point3D
   * @return       Distance to other Point3D as double
   */
  public double getDistanceSquared(Point3D point) {
    return getSquareDifference(this.x, point.x) +
      getSquareDifference(this.y, point.y) +
      getSquareDifference(this.z, point.z);
  }

  /**
   * Compute the square difference of two doubles
   * @param   u1 A double
   * @param   u2 Another double
   * @return  Square difference of doubles
   */
  private static double getSquareDifference(double u1, double u2) {
    return Math.pow(u1 - u2, 2);
  }

  @Override
  public String toString() {
    return "(" + this.x + ", " + this.y + ", " + this.z + ")";
  }

  @Override
  public boolean equals(Object o) {
    if (o instanceof Point3D) {
      Point3D point = (Point3D) o;
      return ((this.x == point.getX()) && (this.y == point.getY()) && (this.z == point.getZ()));
    }
    else return false;
  }

  @Override
  public int hashCode() {
    //Duplicated hash implementation from javafx.geometry.Point3D
    if (hash == 0) {
      long bits = 7L;
      bits = 31L * bits + Double.doubleToLongBits(x);
      bits = 31L * bits + Double.doubleToLongBits(y);
      bits = 31L * bits + Double.doubleToLongBits(z);
      hash = (int) (bits ^ (bits >> 32));
    }
    return hash;  }
}
