//#include"Vector.h"
//#include"Functions.h"
#include"Ray.h"
#include<vector>
#include<math.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#define _USE_MATH_DEFINES
using namespace std;

void shoot(Ray& r, bool change) {
  if ((r.n == 5) || (r.w < 0.0000001f)) return;
  if (change) swap(n1, n2);
  if (r.cross()) {                                                      // esli luch ne vyhodit vne kletki
    Ray r1 = r.refl();                                            // sozdanie otrajennogo lucha
    Ray r2 = r.refr();                                            // sozdanie prelomlennogo lucha
    shoot(r1, false);                                                 // pusk otrajennogo    
    shoot(r2, true);                                                 // pusk prelomlennogo
  }
  else {                                                                  // luch vyhodit za kletku
    pluss(r.direction, r.w);                                                       // podsvet sektora
    if (change) swap(n1, n2);
    return;
  }
  if (change) swap(n1, n2);
  return;
}


double a = 1, b = 2, n1 = 1.0, n2 = 1.33, h = 0.0001, phi = 0.;  // input parameters
vector<double> collect(360,0);

void main() {
  ofstream out("e-133-xya-12-all.txt"), out2("el2.txt");
  Vector normal(2);  // normal
  Vector vec(2);  // ray
  double currY = 2 * b;
  Vector dir(2); dir[0] = 1.0;

  for (int i = 0; i < 360; i++){
    currY = 2* b;
    while (currY > -2 * b) {
      Vector pt(-5.0, currY);
      Ray primary(pt, dir, 1.0, 0, 0, 0.);
      if (primary.cross())  shoot(primary, false);
      currY -= h;
    }
    phi += M_PI / 180.0;
  }


  double sum = 0; for (int i = 0; i < collect.size(); i++) sum += collect[i]; cout << sum << endl;

  vector<double>::iterator m = max_element(collect.begin(), collect.end());

  out.clear();
  for (int i = 0; i < collect.size(); i++) {
    out << collect[i] / (*m) << endl; out2 << collect[i] << endl;
  }
}