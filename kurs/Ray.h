#pragma once
#include"Functions.h"
//#include"Vector.h"
#include<math.h>

extern double a, b, n1, n2, h, phi;

class Ray {
public:
  Vector point;
  Vector direction;
  double w;
  int n;
  int env;
  double distance;

  Ray(Vector _point, Vector _direction, double _w, int _n, int _env, double _distance) { point = _point; direction = _direction; w = _w; n = _n; env = _env; distance = _distance; };
  Ray() { w = 0; n = 0; env = 0; };
  Ray(const Ray& r) { point = r.point; direction = r.direction; w = r.w; n = r.n; env = r.env; }
  Ray(Ray& r) { point = r.point; direction = r.direction; w = r.w; n = r.n; env = r.env; }

  bool cross();
  Vector cross_point();
  Ray refl();
  Ray refr();

  Ray& operator=(const Ray& r) { point = r.point; direction = r.direction; w = r.w; n = r.n; env = r.env; }

};