#pragma once
#ifndef RECORDER_H
#define RECORDER_H


#include"Intersection.h"
#include<vector>

using namespace std;

class Recorder {
private:
  double reflCoef;
  double distance;
  double resolution;
  vector<double> record;
public:
  Recorder();
  Recorder(double _resolution, double _distance, double _reflCoef);
  Recorder(const Recorder& rec);

  void recordRay(const Ray& ray);

  double getRec(int i) const;

  Recorder& operator=(const Recorder& rec);
  
  vector<double> absorbRecorders(vector<Recorder> arrayRecorders) const;

};

#endif // !RECORDER_H
