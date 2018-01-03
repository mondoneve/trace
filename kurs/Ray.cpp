#include"Ray.h"

bool Ray::cross() {
  /*double A = b*b*direction[0] * direction[0] + a*a*direction[1] * direction[1];
  double B = 2 * (point[0] * direction[0] * b*b + a*a*point[1] * direction[1]);
  double C = b*b*point[0] * point[0] + a*a*point[1] * point[1] - a*a*b*b;
  double D = B*B - 4 * A*C;
  double t1 = 0.5*(-B + sqrt(D));
  double t2 = 0.5*(-B - sqrt(D));*/
  double k1 = direction[0] * cos(phi) + direction[1] * sin(phi);
  double k2 = point[0] * cos(phi) + point[1] * sin(phi);
  double k3 = -direction[0] * sin(phi) + direction[1] * cos(phi);
  double k4 = -point[0] * sin(phi) + point[1] * cos(phi);
  double A = b*b*k1*k1 + a*a*k3*k3;
  double B = 2 * (b*b*k1*k2 + a*a*k3*k4);
  double C = b*b*k2*k2 + a*a*k4*k4 - a*a*b*b;
  double D = B*B - 4 * A*C;
  double t1 = 0.5*(-B - sqrt(D)) / A;
  double t2 = 0.5*(-B + sqrt(D)) / A;
  if (t1 > 0.00001 || t2 > 0.00001) return true;
  return false;
}
Vector Ray::cross_point() {
  Vector res(2);
  /*double A = b*b*direction[0] * direction[0] + a*a*direction[1] * direction[1];
  double B = 2 * (point[0] * direction[0] * b*b + a*a*point[1] * direction[1]);
  double C = b*b*point[0] * point[0] + a*a*point[1] * point[1] - a*a*b*b;
  double D = B*B - 4 * A*C;*/
  double k1 = direction[0] * cos(phi) + direction[1] * sin(phi);
  double k2 = point[0] * cos(phi) + point[1] * sin(phi);
  double k3 = -direction[0] * sin(phi) + direction[1] * cos(phi);
  double k4 = -point[0] * sin(phi) + point[1] * cos(phi);
  double A = b*b*k1*k1 + a*a*k3*k3;
  double B = 2 * (b*b*k1*k2 + a*a*k3*k4);
  double C = b*b*k2*k2 + a*a*k4*k4 - a*a*b*b;
  double D = B*B - 4 * A*C;
  double t1 = 0.5*(-B - sqrt(D))/A;
  double t2 = 0.5*(-B + sqrt(D))/A;
  if (t1 > 0.00001) return point+direction*t1;
  if (t2 > 0.00001) return point+direction*t2;
  printf("+++\n");
  return point*0.0;
}

Ray Ray::refl() {
  Vector cp = cross_point();
  double length = dist(point, cp);

  double krefl = 0;
  double alpha = 0;
  double beta = 0;
  Vector newdir;

  if (env == 1) {
    newdir = reflect(direction, -getnorm(cp));
    alpha = angle(-direction, -getnorm(cp));
  }
  else
  {
    newdir = reflect(direction, getnorm(cp));
    alpha = angle(-direction, getnorm(cp));
  }

  if (abs(n1*sin(alpha) / n2) > 1 || (alpha==0)) krefl = 1.0;
  else {
    beta = asin(n1*sin(alpha) / n2);
    krefl = (pow(tan(alpha - beta) / tan(alpha + beta), 2) + pow(sin(alpha - beta) / sin(alpha + beta), 2)) * 0.5;
  }

  Ray res(cp, newdir, w * krefl , n + 1, env, distance + length);
  return res;
}

Ray Ray::refr() {
  Vector cp = cross_point();
  double length = dist(point, cp);

  double krefl = 0;
  double alpha = 0;
  double beta = 0;
  Vector newdir;

  if (env == 1) {
    newdir = refract(direction, -getnorm(cp));
    alpha = angle(-direction, -getnorm(cp));
  }
  else {
    newdir = refract(direction, getnorm(cp));
    alpha = angle(-direction, getnorm(cp));
  }

  if (abs(n1*sin(alpha) / n2) > 1 || (alpha == 0)) {
    krefl = 1;
    Ray res(cp, cp, 0.0, n + 1, 0., 0.);
    return res;
  }
  else {
    beta = asin(n1*sin(alpha) / n2);
    krefl = (pow(tan(alpha - beta) / tan(alpha + beta), 2) + pow(sin(alpha - beta) / sin(alpha + beta), 2)) * 0.5;
  }

  Ray res(cp, newdir, (1-krefl)*w, n + 1, abs(env - 1), distance + length);
  return res;
}
