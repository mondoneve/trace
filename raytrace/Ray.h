#pragma once
#ifndef RAY_H
#define RAY_H
#include"Vector.h"

class Ray {
private:
  double waveLen;
  Point point;
  Vector direction; // normalized
  double weight;  // 0..1
  double distance;  // 0..2pi
  int reflectCounter;
public:
  Ray(); // constructs all zero ray
  Ray(Point p, Vector d, double w, double dist, int r, double wavelen);
  Ray(const Ray& v);

  Point getPoint() const;
  Vector getDirection() const;
  int getReflectCounter() const;
  double getWaveLen() const;
  double getWeight() const;
  double getDistance() const;


  Point runFor(double time) const;

  Ray& operator=(const Ray& v);

};

#endif // !RAY_H
