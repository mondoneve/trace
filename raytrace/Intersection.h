#pragma once
#include"CellModel.h"


class Intersection : public Point {
private:
  Ray originRay;
  CellModel cell;
  Ray reflectedRay;
  Ray refractedRay;
  double time;
  Point reflectedPoint;
  Point refractedPoint;

  void setTimeAndPoints(const Ray& r, const CellModel& c);
public:
  Intersection();
  Intersection(const Ray& ray, const CellModel& model);
  Intersection(const Intersection& i);

  static bool isIntersect(const Ray& r, const CellModel& c);

  Ray getReflected() const;
  Ray getRefracted() const;

};

