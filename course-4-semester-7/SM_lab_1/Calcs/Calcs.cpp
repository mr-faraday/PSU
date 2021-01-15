#include <math.h>
#include <stdio.h>

int const n = 10000;
int const m = 5;

int main() {
  int i, j;
  double w, x, y, h, delta, z, z1, z2, angle, res[3][n + 1], a[m + 2], sum, sum1, sum2;
  a[0] = 1.0;
  a[1] = 5.0;
  a[2] = 15.0;
  a[3] = 48.0;
  a[4] = 44.0;
  a[5] = 74.0;
  w = 0.0;
  h = 0.1;

  angle = 0.0;
  for (j = 1; j <= n; j++) {
    sum = 0.0;
    sum1 = 0.0;
    sum2 = 0.0;
    for (i = 0; i <= m; i++) {
      if (i % 4 == 0) {
        sum1 = sum1 + pow(w, double(m - i)) * a[i];
      } else if (i % 4 == 1) {
        sum2 = sum2 + pow(w, double(m - i)) * a[i];
      } else if (i % 4 == 2) {
        sum1 = sum1 - pow(w, double(m - i)) * a[i];
      } else if (i % 4 == 3) {
        sum2 = sum2 - pow(w, double(m - i)) * a[i];
      }
    }
    w = w + h;
    res[1][j] = sum1;
    res[2][j] = sum2;
  }
  for (j = 1; j <= n - 1; j++) {
    z1 = sqrt(res[1][j] * res[1][j] + res[2][j] * res[2][j]);
    z2 = sqrt(res[1][j + 1] * res[1][j + 1] + res[2][j + 1] * res[2][j + 1]);
    z = acos((res[1][j] * res[1][j + 1] + res[2][j] * res[2][j + 1]) / (z1 * z2));
    angle = angle + z;
  }

  printf("d(fi)=%.8lf pi*n/2=%.4lf\n'n'= %.8lf\ndelta=%.16lf\n", angle, double(m) * asin(1.0), angle / asin(1.0), angle - double(m) * asin(1.0));
  delta = angle - double(m) * asin(1.0);
  if (sqrt(delta * delta) <= 0.01) {
    printf("solves is stable\n");
  } else {
    printf("solves is not stable\n");
  }
}
