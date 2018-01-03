#include"Vector.h"

Vector::Vector(int _n) { v.resize(_n,0); }
Vector::Vector(double x, double y) { v.push_back(x); v.push_back(y); }
Vector::Vector(vector<double> data) { v = data; }
Vector::Vector(const Vector& vc) { v = vc.v; }

//void Vector::pb(double a) { v.push_back(a); }

Vector Vector::operator+(Vector v2) {
  Vector result(*this);
  for (int i = 0; i < size(); i++) result[i]=v[i] + v2[i];
  return result;
}
Vector Vector::operator-(Vector v2) {
  Vector result = *this + (-v2);
  return result;
}
Vector Vector::operator-() {
  Vector result(*this);
  for (int i = 0; i < size(); i++) result[i]=-v[i];
  return result;
}
Vector& Vector::operator=(Vector v2) {
  v = v2.v;
  return *this;
}
Vector Vector::operator*(Vector v2) {
  Vector result(*this);
  for (int i = 0; i < v2.size(); i++) result[i] = v[i] * v2[i];
  return result;
}
Vector Vector::operator*(double a){
  Vector result(*this);
  for (int i = 0; i < size(); i++) result[i] = v[i] * a;
  return result;
}
Vector Vector::operator/(Vector v2) {
  Vector result(*this);
  for (int i = 0; i < v2.size(); i++) result[i]=v[i] / v2[i];
  return result;
}
Vector Vector::operator/(const double& a){
  Vector result(*this);
  for (int i = 0; i < size(); i++) result[i]=v[i] / a;
  return result;
}
double& Vector::operator[](int i) { return v[i]; }
