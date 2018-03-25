#include "Recorder.h"
#include<iostream>
Recorder::Recorder() {}

Recorder::Recorder(double _resolution, double _distance, double _reflCoef) {
  reflCoef = _reflCoef;
  distance = _distance;
  resolution = _resolution;
  record.resize((int)(360 / resolution), 0.0);
}

Recorder::Recorder(const Recorder & rec) {
  reflCoef = rec.reflCoef;
  distance = rec.distance;
  resolution = rec.resolution;
  record.resize((int)(360 / resolution), 0.0);
  for (int i = 0; i < record.size(); i++) record[i] = rec.record[i];
}

void Recorder::recordRay(const Ray & ray) {
  double sector = ray.getDirection().getAzimuth().getDegree();
  int index = floor(sector / resolution);
  if (index >= record.size()) {
    index = 0; cout << "hey bitch  ";
  }
  if (index < 0) {
    index = 0; cout << "HAY BITCH  ";
  }
  Angle polar(index*resolution + 0.5*resolution, DEGREE);
  double time = (polar.tg()*(distance*polar.sinus() - ray.getPoint().getY()) - ray.getPoint().getX() + distance*polar.cosinus()) / (ray.getDirection().getX() + polar.tg()*ray.getDirection().getY());
  Point intersection = ray.runFor(time);
  double distancePlus = ray.getPoint().distanceToPoint(intersection) / reflCoef;
  record[index] += ray.getWeight()*cos(M_PI*2*(ray.getDistance()+distancePlus)/ray.getWaveLen());
  //record[index] += ray.getWeight();
}

double Recorder::getRec(int i) const {
  return record[i];
}

Recorder& Recorder::operator=(const Recorder& rec) {
  reflCoef = rec.reflCoef;
  distance = rec.distance;
  resolution = rec.resolution;
  record.resize((int)(360 / resolution), 0.0);
  for (int i = 0; i < record.size(); i++) record[i] = rec.record[i];
  return *this;
}

vector<double> Recorder::absorbRecorders(vector<Recorder> arrayRecorders) const {
  vector<double> res(record.size(), 0.0);
  for (int i = 0; i < arrayRecorders.size(); i++)
    for (int j = 0; j < arrayRecorders[i].record.size(); j++) res[j] += arrayRecorders[i].record[j];
  return res;
}
