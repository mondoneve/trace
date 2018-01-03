#include"Functions.h"

double dist(Vector a, Vector b) {
  Vector v = a - b;
  return sqrt(v[0] * v[0] + v[1] * v[1]);
}

double dot(Vector a, Vector b) {
  double res = 0;
  for (int i = 0; i < a.size(); i++) res += a[i] * b[i];
  return res;
}

Vector reflect(Vector v, Vector n) {
  return v - n * 2 * dot(v, n);
}

Vector normalize(Vector x) {
  double k = 0;
  Vector res = x;
  for (int i = 0; i < x.size(); i++) k += x[i] * x[i];
  k = sqrt(k);
  res =  res / k;
  return res;
}


Vector refract(Vector v, Vector n) {
  v = v * n1;
  double d = dot(v, n);
  if (d == 0) return n;
  v = v + n*d*(sqrt((n2*n2 - n1*n1) / pow(d, 2) + 1) - 1);
  return (normalize(v));
}

double angle(Vector a, Vector b) {
  return acos(dot(normalize(a), normalize(b)));
}


int pts(Vector v) {
  double at = 0;
  if (v[0] == 0)
    if (v[1] > 0) return 90;
    else return 270;
  at = atan(abs(v[1]) / (v[0])) * 180 / 3.14159265359;
  if ((v[0] < 0)&(v[1]>0)) return (180 - (int)(at));
  if ((v[0] < 0)&(v[1]<0)) return (180 + (int)(at));
  if ((v[0] > 0)&(v[1]<0)) return (360 - (int)(at));
  if (at < 0 || at>360)
    bool f;
  return (int)(at);
}

void pluss(Vector v, double w) {
  int i = pts(v);
  if (w < 0.000000001f) w = 0;
  if (i == 360) i = 0;
  collect[i] += w / 360.0;
  return;
}

Vector getnorm(Vector x) {
  Vector res(2);
  /*res[0] = x[0] * pow(b, 2);
  res[1] = x[1] * pow(a, 2);*/
  double m1 = x[0] * cos(phi) + x[1] * sin(phi);
  double m2 = -x[0] * sin(phi) + x[1] * cos(phi);
  res[0] = m1*cos(phi) / a / a - m2*sin(phi) / b / b;
  res[1] = m1*sin(phi) / a / a + m2*cos(phi) / b / b;
  return normalize(res);
}
