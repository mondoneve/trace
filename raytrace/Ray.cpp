#include "Ray.h"

Ray::Ray() {
  waveLen = 0.0; weight = 0.0; reflectCounter = 0; distance = 0.0;
}

Ray::Ray(Point p, Vector d, double w, double dist, int r, double wavelen) {
  point = p; direction = d; weight = w; distance = dist; reflectCounter = r; waveLen = wavelen;
}

Ray::Ray(const Ray & v) {
  *this = v;
}

Point Ray::getPoint() const {
  return point;
}

Vector Ray::getDirection() const {
  return direction;
}

int Ray::getReflectCounter() const {
  return reflectCounter;
}

double Ray::getWaveLen() const {
  return waveLen;
}

double Ray::getWeight() const {
  return weight;
}

double Ray::getDistance() const {
  return distance;
}


Point Ray::runFor(double time) const {
  Point res(point.getX() + time*direction.getX(), point.getY() + time*direction.getY(), point.getZ() + time*direction.getZ());
  return res;
}

Ray & Ray::operator=(const Ray& v) {
  point = v.getPoint(); direction = v.getDirection(); reflectCounter = v.getReflectCounter(); distance = v.getDistance(); waveLen = v.getWaveLen(); weight = v.getWeight();
  return *this;
}


