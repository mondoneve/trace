#include "CellModel.h"
#include<iostream>

CellModel::CellModel() {
  insideN = outsideN = a = b = 0.0;
}

CellModel::CellModel(double in, double out, double _a, double _b, double angle) {
  insideN = in; outsideN = out; a = _a; b = _b; turn.setRadian(angle);
}

CellModel::CellModel(const CellModel & cm) {
  insideN = cm.getInsideN();
  outsideN = cm.getOutsideN();
}

double CellModel::getInsideN() const {
  return insideN;
}

double CellModel::getOutsideN() const {
  return outsideN;
}

Angle CellModel::getTurn() const {
  return turn;
}

double CellModel::getA() const {
  return a;
}

double CellModel::getB() const {
  return b;
}

bool CellModel::isOnBorder(const Point & r) const {
  double sum = pow((r.getX()*turn.cosinus() + r.getY()*turn.sinus()) / a, 2) + pow((-r.getX()*turn.sinus() + r.getY()*turn.cosinus()) / b, 2);
  //if ((sum - 1.0 < VERY_SMALL)&& (sum - 1.0 > -VERY_SMALL)) return true;
  if (sum < 1.0) return true;
  return false;
}

bool CellModel::intersectsWith(const Ray & r) const {
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
  if (t1 > VERY_SMALL || t2 > VERY_SMALL) return true;
  return false;
}

Point CellModel::intersectionWith(const Ray & r) const {
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
  if (t1 > 0) return r.runFor(t1);
  if (t2 > 0) return r.runFor(t2);
  Point bad(0.0, 0.0, 0.0);
  return bad;
}

Vector CellModel::getNormal(const Point& p) const {
  double m1 = p.getX() * turn.cosinus() + p.getY() * turn.sinus();
  double m2 = -p.getX() * turn.sinus() + p.getY() * turn.cosinus();
  Vector res(m1*turn.cosinus() / a / a - m2*turn.sinus() / b / b, m1*turn.sinus() / a / a + m2*turn.cosinus() / b / b, 0.0);
  res.normalize();
  return res;
}

/*
Ray CellModel::refractRay(const Ray & r) const {
  Point intersection = intersectionWith(r);
  double weightCoeff = 0.;
  double nHome, nOut;
  Angle alpha;
  Angle beta;
  Vector newDirection;
  
  if (isOnBorder(r.getPoint())) { 
    nHome = insideN;
    //nOut = outsideN;
    alpha = (-r.getDirection()).getAngleTo(-getNormal(intersection));
    newDirection = r.getDirection().refract(-getNormal(intersection), nHome, nOut);
  } else {
    //nHome = outsideN;
    nOut = insideN;
    alpha = (-r.getDirection()).getAngleTo(getNormal(intersection));
    newDirection = r.getDirection().refract(getNormal(intersection), nHome, nOut);
  }

  double distancePlus = r.getPoint().distanceToPoint(intersection) / nHome;

  if ((nHome*alpha.sinus() / nOut) > 1) {weightCoeff = 0; std::cout << "FULL   ";} // full reflection
  else if (alpha.getRadian(FROM_ZERO) == 0){ weightCoeff = 0.5*4*nOut*nHome/(nOut+nHome)/ (nOut + nHome); std::cout << "NORM   ";} // normal falling
  else {
    beta.setRadian(asin(nHome*alpha.sinus() / nOut));
    if (((alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)) - M_PI*0.5 > -VERY_SMALL) &&((alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)) - M_PI*0.5 < VERY_SMALL)) { weightCoeff = 0.5*pow(2 * beta.sinus()*alpha.cosinus() / (alpha + beta).sinus(), 2); std::cout << "BREWSTER   ";}//0.5*(alpha.sinus()*alpha.sinus() + (alpha - beta).sinus());  // bruster case
    else weightCoeff = 1 - (pow((alpha - beta).tg() / (alpha + beta).tg(), 2) + pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2))*0.5;//(pow(2*beta.sinus()*alpha.cosinus()/(alpha+beta).sinus(),2)+pow(2*beta.sinus()*alpha.cosinus()/(alpha+beta).sinus()/(alpha-beta).cosinus(),2))*0.5;//0.5*((pow(alpha.sinus(), 2) + (alpha - beta).sinus()) / pow((alpha + beta).sinus()*(alpha - beta).cosinus(), 2) + (alpha.sinus()*alpha.sinus() + (alpha - beta).sinus()) / pow((alpha + beta).sinus(), 2));
  }

  if ((nHome*alpha.sinus() / nOut) > 1) weightCoeff = 1.0;  // full reflection
  else if (alpha.getRadian(FROM_ZERO) == 0) weightCoeff = 0.5*pow((nOut - nHome) / (nOut + nHome), 2); // normal falling
  else {
    beta.setRadian(asin(nHome*alpha.sinus() / nOut));
    if (((alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)) - M_PI*0.5 > -VERY_SMALL) && ((alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)) - M_PI*0.5 <  VERY_SMALL)) weightCoeff = 0.5*pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2);//0.5*pow((alpha - beta).sinus()*(alpha - beta).sinus(),2);  // bruster case
                                                                                                                                                                                                                                                              //else weightCoeff = (pow((alpha - beta).tg() / (alpha + beta).tg(), 2) + pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2))*0.5;//0.5*(pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2) + pow((alpha - beta).tg() / (alpha + beta).tg(), 2));
    else weightCoeff = 0.5*(pow(tan(alpha.getRadian(FROM_ZERO) - beta.getRadian(FROM_ZERO)) / tan(alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)), 2) + pow(sin(alpha.getRadian(FROM_ZERO) - beta.getRadian(FROM_ZERO)) / sin(alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)), 2));
  } 
  weightCoeff = (pow((nHome*alpha.cosinus() - nOut*beta.cosinus()) / (nHome*alpha.cosinus() + nOut*beta.cosinus()), 2) + pow((nHome*beta.cosinus() - nOut*alpha.cosinus()) / (nHome*beta.cosinus() + nOut*alpha.cosinus()), 2))*0.5;
  weightCoeff = 1 - weightCoeff;

  Point shifted(intersection.getX() + (r.runFor(VERY_SMALL).getX() - r.getPoint().getX()), intersection.getY() + (r.runFor(VERY_SMALL).getY() - r.getPoint().getY()), intersection.getZ() + (r.runFor(VERY_SMALL).getZ() - r.getPoint().getZ()));
  Ray res(shifted, newDirection, weightCoeff * r.getWeight(), r.getDistance()+distancePlus, r.getReflectCounter(), r.getWaveLen());

  return res;
}

Ray CellModel::reflectRay(const Ray & r) const {
  Point intersection = intersectionWith(r);
  double weightCoeff = 0.;
  double nHome, nOut;
  Angle alpha;
  Angle beta;
  Vector newDirection;

  if (isOnBorder(r.getPoint())) {
    nHome = insideN;
    nOut = outsideN;
    alpha = (-r.getDirection()).getAngleTo(-getNormal(intersection));
    newDirection = r.getDirection().reflect(-getNormal(intersection));
  }
  else {
    nHome = outsideN;
    nOut = insideN;
    alpha = (-r.getDirection()).getAngleTo(getNormal(intersection));
    newDirection = r.getDirection().reflect(getNormal(intersection));
  }

  double distancePlus = r.getPoint().distanceToPoint(intersection) / nHome;

  if ((nHome*alpha.sinus() / nOut) > 1) weightCoeff = 1.0;  // full reflection
  else if (alpha.getRadian(FROM_ZERO) == 0) weightCoeff = 0.5*pow((nOut - nHome) / (nOut + nHome), 2); // normal falling
  else {
    beta.setRadian(asin(nHome*alpha.sinus() / nOut));
    if (((alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)) - M_PI*0.5 > -VERY_SMALL) &&((alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)) - M_PI*0.5 <  VERY_SMALL)) weightCoeff = 0.5*pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2);//0.5*pow((alpha - beta).sinus()*(alpha - beta).sinus(),2);  // bruster case
    //else weightCoeff = (pow((alpha - beta).tg() / (alpha + beta).tg(), 2) + pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2))*0.5;//0.5*(pow((alpha - beta).sinus() / (alpha + beta).sinus(), 2) + pow((alpha - beta).tg() / (alpha + beta).tg(), 2));
    else weightCoeff = 0.5*(pow(tan(alpha.getRadian(FROM_ZERO) - beta.getRadian(FROM_ZERO)) / tan(alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)), 2) + pow(sin(alpha.getRadian(FROM_ZERO) - beta.getRadian(FROM_ZERO)) / sin(alpha.getRadian(FROM_ZERO) + beta.getRadian(FROM_ZERO)), 2));
  }
  weightCoeff = (pow((nHome*alpha.cosinus() - nOut*beta.cosinus()) / (nHome*alpha.cosinus() + nOut*beta.cosinus()), 2) + pow((nHome*beta.cosinus() - nOut*alpha.cosinus()) / (nHome*beta.cosinus() + nOut*alpha.cosinus()), 2))*0.5;


  Point shifted(intersection.getX() - (r.runFor(VERY_SMALL).getX() - r.getPoint().getX()), intersection.getY() - (r.runFor(VERY_SMALL).getY() - r.getPoint().getY()), intersection.getZ() - (r.runFor(VERY_SMALL).getZ() - r.getPoint().getZ()));
  Ray res(shifted, newDirection, weightCoeff * r.getWeight(), r.getDistance() + distancePlus, r.getReflectCounter() + 1, r.getWaveLen());

  return res;
}
*/