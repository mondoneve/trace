#pragma once
//#include"Ray.h"
#include"Vector.h"
//#include"Ray.h"
#define _USE_MATH_DEFINES

using namespace std;

extern vector<double> collect; 
extern double n1, n2, a, b, phi;

double dist(Vector a, Vector b);

double dot(Vector a, Vector b);

Vector reflect(Vector v, Vector n);

Vector normalize(Vector x);

Vector refract(Vector v, Vector n);

double angle(Vector a, Vector b);


int pts(Vector v);

void pluss(Vector v, double w);

Vector getnorm(Vector x);
