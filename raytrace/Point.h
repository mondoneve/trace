#pragma once
#ifndef  POINT_H
#define  POINT_H

#define VERY_SMALL 0.000000001

#include<math.h>
class Vector;


class Point {
protected:
  double x, y, z;


public:
  Point();  // constructs all zero point
  Point(double _x, double _y, double _z);
  Point(const Point& p);

  static Point make_point(double _x, double _y, double _z);

  double getX() const;
  double getY() const;
  double getZ() const;

  void setX(double val);
  void setY(double val);
  void setZ(double val);
  void setXYZ(double _x, double _y, double _z);

  double distanceToPoint(const Point& p) const;
  Vector getVectorToPoint(const Point& p) const;

  Point operator+(const Point& p) const;
  Point operator-() const;
  Point operator-(const Point& p) const;
  Point& operator=(const Point& p);
  bool operator==(const Point& p) const;
  bool operator!=(const Point& p) const;
  void operator<<(ofstream& ofs) const;
};

#endif // ! POINT_H
