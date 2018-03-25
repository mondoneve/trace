#pragma once
#ifndef CELL_MODEL_H
#define CELL_MODEL_H

#include"Ray.h"

class CellModel{
private:
  double outsideN;
  double insideN;
  double a;
  double b;
  Angle turn;
public:
  CellModel();
  CellModel(double in, double out, double _a, double _b, double angle);
  CellModel(const CellModel& cm);

  double getInsideN() const;
  double getOutsideN() const;
  Angle getTurn() const;
  double getA() const;
  double getB() const;

  bool isOnBorder(const Point& r) const;

  bool intersectsWith(const Ray& r) const;
  Point intersectionWith(const Ray& r) const;
  Vector getNormal(const Point& p) const;

  //Ray refractRay(const Ray& r) const;
  //Ray reflectRay(const Ray& r) const;

};

#endif // !CELL_MODEL_H
