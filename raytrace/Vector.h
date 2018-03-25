#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#define _USE_MATH_DEFINES
#include"Point.h"
#include"Angle.h"
#include<math.h>


class Vector : public Point {

public:
  Vector(); // constructs all zero vector
  Vector(const Point& p);
  Vector(double _x, double _y, double _z);
  Vector(Angle a, double r);
  Vector(const Vector& v);

  static Vector make_vector(double _x, double _y, double _z);

  void normalize();
  Vector getWithNormOf(double a) const;

  double getLength() const;
  Angle getAzimuth() const;
  Angle getAngleTo(const Vector& v) const;  // returns less angle (through dot)

  Vector refract(const Vector& n, double nHome, double nOut) const;
  Vector reflect(const Vector& n) const;

  double dot(const Vector& v) const;
  Vector operator+(const Vector& v) const;
  Vector operator-(const Vector& v) const;
  Vector operator-() const;
  Vector& operator=(const Vector& v);
  Vector operator*(const Vector& v) const; // multiplying components
  Vector operator*(double a) const;
  Vector operator/(const Vector& v) const;
  Vector operator/(double a) const;
};

#endif // !VECTOR_H
