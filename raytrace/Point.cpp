#include "Point.h"
#include "Vector.h"

double Point::distanceToPoint(const Point& p) const {
  return sqrt(pow(x-p.getX(),2)+pow(y-p.getY(),2)+pow(z-p.getZ(),2));
}

Vector Point::getVectorToPoint(const Point & p) const {
  Vector v(p.getX() - x, p.getY() - y, p.getZ() - z);
  v.normalize();
  return v;
}

Point Point::operator+(const Point & p) const {
  Point res(x + p.x, y + p.y, z + p.z);
  return res;
}

Point Point::operator-() const {
  Point res(-x, -y, -z);
  return res;
}

Point Point::operator-(const Point & p) const {
  return *this + (-p);
}

Point::Point() {
  x = 0; y = 0; z = 0;
}

Point::Point(double _x, double _y, double _z) {
  x = _x; y = _y; z = _z;
}

Point::Point(const Point & p) {
  x = p.getX(); y = p.getY(); z = p.getZ();
}

Point Point::make_point(double _x, double _y, double _z) {
  Point res(_x, _y, _z);
  return res;
}

double Point::getX() const {
  return x;
}

double Point::getY() const {
  return y;
}

double Point::getZ() const {
  return z;
}

void Point::setX(double val) {
  x = val;
}

void Point::setY(double val) {
  y = val;
}

void Point::setZ(double val) {
  z = val;
}

void Point::setXYZ(double _x, double _y, double _z) {
  x = _x; y = _y; z = _z;
}

Point & Point::operator=(const Point& p) {
  setXYZ(p.getX(), p.getY(), p.getZ());
  return *this;
}

bool Point::operator==(const Point& p) const {
  if (x != p.getX() || y != p.getY() || z != p.getZ()) return false;
  return true;
}

bool Point::operator!=(const Point& p) const {
  if (*this == p) return false;
  return true;
}
