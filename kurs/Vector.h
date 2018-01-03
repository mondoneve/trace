#pragma once
#include<vector>

using namespace std;

class Vector {
public:
  vector<double> v;

  Vector() {}
  Vector(int _n);
  Vector(double x, double y);
  Vector(vector<double> data);
  Vector(const Vector& vc);

 // void pb(double a);

  Vector operator+(Vector v2);
  Vector operator-(Vector v2);
  Vector operator-();
  Vector& operator=(Vector v2);
  Vector operator*(Vector v2);
  Vector operator*(double a);
  Vector operator/(Vector v2);
  Vector operator/(const double& a);
  double& operator[](int i);

  int size() { return v.size(); }

};
