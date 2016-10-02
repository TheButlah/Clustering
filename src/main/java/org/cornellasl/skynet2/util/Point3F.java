package org.cornellasl.skynet2.util;

/**
 * Class describing point in 3D space with float precision
 */
public class Point3F {

  // Cartesian coordinates x, y, z
  private float x, y, z;

  /**
   * Create a Point3D object with coordinates x, y, z, specified as floats
   * @param x x-coordinate
   * @param y y-coordinate
   * @param z z-coordinate
   */
  public Point3F(float x, float y, float z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  /**
   * x-coordinate getter
   * @return x-coordinate float
   */
  public float getX() { return this.x; }

  /**
   * y-coordinate getter
   * @return y-coordinate float
   */
  public float getY() { return this.y; }

  /**
   * z-coordinate getter
   * @return z-coordinate float
   */
  public float getZ() { return this.z; }

  /**
   * Compute the 2-norm distance squared to another Point3D
   * @param  point Another Point3D
   * @return       Distance to other Point3D as float
   */
  public float getDistanceSquared(Point3F point) {
    return getSquareDifference(this.x, point.x) +
      getSquareDifference(this.y, point.y) +
      getSquareDifference(this.z, point.z);
  }

  /**
   * Compute the square difference of two float
   * @param   u1 A float
   * @param   u2 Another float
   * @return  Square difference of float
   */
  public static float getSquareDifference(float u1, float u2) {
    float diff = u1-u2;
    return diff*diff;
  }

  @Override
  public String toString() {
    return "(" + this.x + ", " + this.y + ", " + this.z + ")";
  }

  @Override
  public boolean equals(Object o) {
    if (o instanceof Point3F) {
      Point3F point = (Point3F) o;
      return ((this.x == point.getX()) && (this.y == point.getY()) && (this.z == point.getZ()));
    }
    else return false;
  }

  @Override
  public int hashCode() {
    return (int) this.x + (int) this.y + (int) this.z;
  }
}
