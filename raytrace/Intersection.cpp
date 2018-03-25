#include "Intersection.h"

Intersection::Intersection() {
  time = 0.0;
}

Intersection::Intersection(const Ray & ray, const CellModel & model) {
  originRay = ray;
  cell = model;
  setTimeAndPoints(ray, model);
  Point thisPoint(x, y, z);
  Vector reflectedDirection;
  Vector refractedDirection;
  Angle alpha;
  Angle beta;
  double nHome;
  double nOut;
  double reflectCoeff;

  if (model.isOnBorder(ray.getPoint())) {
    nHome = model.getInsideN();
    nOut = model.getOutsideN();
    alpha = (-ray.getDirection()).getAngleTo(-model.getNormal(thisPoint));
    refractedDirection = ray.getDirection().refract(-model.getNormal(thisPoint), nHome, nOut);
    reflectedDirection = ray.getDirection().reflect(-model.getNormal(thisPoint));
  }
  else {
    nHome = model.getOutsideN();
    nOut = model.getInsideN();
    alpha = (-ray.getDirection()).getAngleTo(model.getNormal(thisPoint));
    refractedDirection = ray.getDirection().refract(model.getNormal(thisPoint), nHome, nOut);
    reflectedDirection = ray.getDirection().reflect(model.getNormal(thisPoint));
  }

  double distancePlus = ray.getPoint().distanceToPoint(thisPoint) / nHome;

  reflectCoeff = (pow((nHome*alpha.cosinus() - nOut*beta.cosinus()) / (nHome*alpha.cosinus() + nOut*beta.cosinus()), 2) + pow((nHome*beta.cosinus() - nOut*alpha.cosinus()) / (nHome*beta.cosinus() + nOut*alpha.cosinus()), 2))*0.5;

  Ray refl(reflectedPoint, reflectedDirection, reflectCoeff * ray.getWeight(), ray.getDistance() + distancePlus, ray.getReflectCounter() + 1, ray.getWaveLen());
  Ray refr(refractedPoint, refractedDirection, (1-reflectCoeff) * ray.getWeight(), ray.getDistance() + distancePlus, ray.getReflectCounter(), ray.getWaveLen());

  reflectedRay = refl;
  refractedRay = refr;
}

Intersection::Intersection(const Intersection & i) {
  originRay = i.originRay; cell = i.cell; reflectedRay = i.reflectedRay; refractedRay = i.refractedRay; x = i.x; y = i.y; z = i.z; time = i.time;
}

void Intersection::setTimeAndPoints(const Ray & r, const CellModel & c) {
  Angle turn = c.getTurn();
  double a = c.getA();
  double b = c.getB();
  Vector cos_sin(turn.cosinus(), turn.sinus(), 0.0);
  Vector msin_cos(-turn.sinus(), turn.cosinus(), 0.0);
  double k1 = r.getDirection().dot(cos_sin);
  double k2 = r.getPoint().getX() * turn.cosinus() + r.getPoint().getY() * turn.sinus();
  double k3 = r.getDirection().dot(msin_cos);
  double k4 = -r.getPoint().getX() * turn.sinus() + r.getPoint().getY() * turn.cosinus();
  double A = b*b*k1*k1 + a*a*k3*k3;
  double B = 2 * (b*b*k1*k2 + a*a*k3*k4);
  double C = b*b*k2*k2 + a*a*k4*k4 - a*a*b*b;
  double D = B*B - 4 * A*C;
  double t1 = 0.5*(-B - sqrt(D)) / A;
  double t2 = 0.5*(-B + sqrt(D)) / A;
  if (t1 > VERY_SMALL) time = t1;
  else time = t2;
  x = r.getPoint().getX() + r.getDirection().getX() * time;
  y = r.getPoint().getY() + r.getDirection().getY() * time;
  z = r.getPoint().getZ() + r.getDirection().getZ() * time;
  reflectedPoint = r.runFor(time - VERY_SMALL);
  refractedPoint = r.runFor(time + VERY_SMALL);
}

Ray Intersection::getReflected() const {
  return reflectedRay;
}

Ray Intersection::getRefracted() const {
  return refractedRay;
}

bool Intersection::isIntersect(const Ray & r, const CellModel & c) {
  Angle turn = c.getTurn();
  double a = c.getA();
  double b = c.getB();
  Vector cos_sin(turn.cosinus(), turn.sinus(), 0.0);
  Vector msin_cos(-turn.sinus(), turn.cosinus(), 0.0);
  double k1 = r.getDirection().dot(cos_sin);
  double k2 = r.getPoint().getX() * turn.cosinus() + r.getPoint().getY() * turn.sinus();
  double k3 = r.getDirection().dot(msin_cos);
  double k4 = -r.getPoint().getX() * turn.sinus() + r.getPoint().getY() * turn.cosinus();
  double A = b*b*k1*k1 + a*a*k3*k3;
  double B = 2 * (b*b*k1*k2 + a*a*k3*k4);
  double C = b*b*k2*k2 + a*a*k4*k4 - a*a*b*b;
  double D = B*B - 4 * A*C;
  double t1 = 0.5*(-B - sqrt(D)) / A;
  double t2 = 0.5*(-B + sqrt(D)) / A;
  if (t1 > 0.0001 || t2 > 0.0001) return true;
  return false;
}


