#include "Angle.h"


double Angle::normalize(double a) {
  if (a > 2 * M_PI) while (a <= 2 * M_PI) a -= 2 * M_PI;
  if (a < -2 * M_PI) while (a >= -2 * M_PI) a += 2 * M_PI;
  return a;
}

Angle::Angle() { angle = 0; }

Angle::Angle(double value, angleMeasure measure) {
  if (measure == RADIAN) angle = value;
  else angle = value * M_PI / 180.0;
  angle = normalize(angle);
  if (angle < 0) angle = M_PI * 2 + angle;
}

Angle Angle::make_angle(double Value, angleMeasure measure) {
  Angle a(Value, measure);
  return a;
}

double Angle::getDegree() const {
  return 180 * angle / M_PI;
}

double Angle::getRadian(angleMode mode) const {
  if (mode == FROM_MINUS && angle > M_PI) return 2 * M_PI - angle;
  return angle;
}

void Angle::setRadian(double val) {
  Angle tmp(val, RADIAN);
  *this = tmp;
}

double Angle::sinus() const {
  return sin(angle);
}

double Angle::cosinus() const {
  return cos(angle);
}

double Angle::tg() const {
  return tan(angle);
}

double Angle::ctan() const {
  return 1.0/tan(angle);
}

Angle & Angle::operator=(const Angle & a) {
  angle = a.getRadian(FROM_ZERO);
  return *this;
}

Angle Angle::operator+(const Angle & a) const {
  Angle res(angle + a.getRadian(FROM_ZERO), RADIAN);
  return res;
}

Angle Angle::operator-() const {
  Angle res(-angle, RADIAN);
  return res;
}

Angle Angle::operator-(const Angle & a) const {
  return *this + (-a);
}

Angle Angle::operator*(double v) const {
  Angle res(angle*v, RADIAN);
  return res;
}

Angle Angle::operator/(double v) const {
  Angle res(angle / v, RADIAN);
  return res;
}
