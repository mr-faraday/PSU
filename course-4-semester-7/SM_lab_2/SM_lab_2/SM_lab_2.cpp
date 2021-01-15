#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <math.h>

int const
  n = 100000,
  n1 = 1000,
  m = n / n1;

double f1(double t, double x, double y);
double f2(double t, double x, double y);

double const alpha = 0.25;

int main() {
  int i, k;
  double k11, k12, k13, k14, k21, k22, k23, k24;
  double x, y;
  double res[6][n1 + 1], h, a, b, t, pi;
  pi = 2.0 * asin(1.0);
  a = 0;
  b = 20.0;
  h = (b - a) / double(n);
  k = 0;
  x = 1;
  y = 0.0;
  t = a;
  res[1][0] = t;
  res[2][0] = x;
  res[3][0] = y;

  for (i = 1; i <= n; i++) {
    k11 = f1(t, x, y);
    k21 = f2(t, x, y);
    k12 = f1(t + h / 2.0, x + h / 2.0 * k11, y + h / 2.0 * k21);
    k22 = f2(t + h / 2.0, x + h / 2.0 * k11, y + h / 2.0 * k21);
    k13 = f1(t + h / 2.0, x + h / 2.0 * k12, y + h / 2.0 * k22);
    k23 = f2(t + h / 2.0, x + h / 2.0 * k12, y + h / 2.0 * k22);
    k14 = f1(t + h, x + h * k13, y + h * k23);
    k24 = f2(t + h, x + h * k13, y + h * k23);
    x = x + h * (k11 + 2.0 * (k12 + k13) + k14) / 6.0;
    y = y + h * (k21 + 2.0 * (k22 + k23) + k24) / 6.0;
    t = t + h;

    if (i % m == 0) {
      k = k + 1;
      res[2][k] = x;
      res[3][k] = y;
      res[1][k] = t;
      printf("x(%.2lf)=%.8lf y(%.2lf)=%.8lf \n", t, x, t, y, t);
    }
  }
 
  remove("105.txt");
  FILE * file;
  file = fopen("105.txt", "w");

  for (i = 0; i <= n1; i++) {
    fprintf(file, "%.16lf   %.16lf \n", res[2][i], res[3][i]);
  }

  fclose(file);
}

double f1(double t, double x, double y) {
  return alpha * x - y - x * (x * x + y * y);
}

double f2(double t, double x, double y) {
  return x + alpha * y - y * (x * x + y * y);
}