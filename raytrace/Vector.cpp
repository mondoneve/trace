#include "Vector.h"
#include <iostream>
Vector::Vector() : Point() {}

Vector::Vector(const Point & p) : Point(p.getX(), p.getY(), p.getZ()) {}

Vector::Vector(double _x, double _y, double _z) : Point(_x, _y, _z) {}

Vector::Vector(const Vector & v) { x = v.getX(); y = v.getY(); z = v.getZ(); }

Vector Vector::make_vector(double _x, double _y, double _z) {
  Vector res(_x, _y, _z);
  return res;
}

void Vector::normalize() { *this = this->getWithNormOf(1.0); }

Vector Vector::getWithNormOf(double a) const {
  double k = sqrt(a)/getLength();
  Vector v(x*k, y*k, z*k);
  return v;
}

double Vector::getLength() const { return sqrt(dot(*this)); }

Angle Vector::getAzimuth() const {
  double a = asin(y / getLength());
  if (x >= 0) {
    Angle res(a, RADIAN);
    return res;
  } else {
    Angle res(M_PI - a, RADIAN);
    return res;
  }
  Angle badAngle(0.0, RADIAN);
  return badAngle;
}

Angle Vector::getAngleTo(const Vector & v) const { Angle a(acos(dot(v) / getLength() / v.getLength()), RADIAN); return a; }

Vector Vector::refract(const Vector & n, double nHome, double nOut) const {
  Vector v = *this; //
  v.normalize();  //
  double r = nHome / nOut; //
  double dotProduct = v.dot(-n);
  //if (dotProduct == 0) { std::cout << "refr0" << std::endl; return n;}
  //v = v + n*dotProduct*(sqrt((nOut*nOut - nHome*nHome) / pow(dotProduct, 2) + 1) - 1);
  v = v*r + n*(r*dotProduct - sqrt(1 - r*r*(1 - dotProduct*dotProduct)));//
  v.normalize();
  return v;
}

Vector Vector::reflect(const Vector & n) const {
  if (n.getLength() - 1.0 > VERY_SMALL || getLength() - 1.0 > VERY_SMALL) std::cout << "BAD" << std::endl;
  Vector v = *this - n * 2 * this->dot(n);
  v.normalize();
  return v;
}

double Vector::dot(const Vector & v) const { return x*v.getX() + y*v.getY() + z*v.getZ(); }

Vector Vector::operator+(const Vector & v) const {
  Vector res(x + v.getX(), y + v.getY(), z + v.getZ());
  return res;
}

Vector Vector::operator-(const Vector & v) const {
  Vector res = *this + (-v);
  return res;
}

Vector Vector::operator-() const {
  Vector res(-x, -y, -z);
  return res;
}

Vector & Vector::operator=(const Vector & v) {
  x = v.getX(); y = v.getY(); z = v.getZ();
  return *this;
}

Vector Vector::operator*(const Vector & v) const {
  Vector res(x*v.getX(), y*v.getY(), z*v.getZ()); return res;
}

Vector Vector::operator*(double a) const {
  Vector res(x*a, y*a, z*a);
  return res;
}

Vector Vector::operator/(const Vector & v) const {
  Vector res(x / v.getX(), y / v.getY(), z / v.getZ());
  return res;
}

Vector Vector::operator/(double a) const {
  Vector res(x / a, y / a, z / a);
  return res;
}
