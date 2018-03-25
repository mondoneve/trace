#pragma once
#ifndef ANGLE_H
#define ANGLE_H
#define _USE_MATH_DEFINES
#include<math.h>

enum angleMeasure {
  RADIAN, DEGREE
};

enum angleMode {
  FROM_ZERO, FROM_MINUS
};

class Angle{
private:
  double angle; // angle in radians
  double normalize(double a);
public:
  Angle(); // constructs zero angle
  Angle(double value, angleMeasure measure);

  static Angle make_angle(double Value, angleMeasure measure);

  double getDegree() const;
  double getRadian(angleMode mode) const;
  void setRadian(double val);

  double sinus() const;
  double cosinus() const;
  double tg() const;
  double ctan() const;

  Angle& operator=(const Angle& a);
  Angle operator+(const Angle& a) const;
  Angle operator-() const;
  Angle operator-(const Angle& a) const;
  Angle operator*(double v) const;
  Angle operator/(double v) const;

};

#endif // !ANGLE_H
