#include <iostream>
#include <string>

using namespace std;

const int kk = 12;
const int p = 257;
const int len = 3 * kk;

int x, y, z, z3;
int d[4][4], delta;
int shifr[4][len + 1], mas0[3][len + 1];
int b[4] = { 0, 123, 66, 38 };
int a[4][4] = {
    {0, 0, 0, 0},
    {0, 3, 0, 5},
    {0, 13, 15, 7},
    {0, 4, 6, 18}
};
string s;
int mas[len + 2];

int f(int delta, int p);

int main()
{
  s = "Moscow State University 265 years";

  s += string(len - s.length(), ' '); // наращиваем строку до len

  d[1][1] = (a[2][2] * a[3][3] - a[2][3] * a[3][2]) % p;
  d[2][1] = (a[3][1] * a[2][3] - a[2][1] * a[3][3]) % p;
  d[3][1] = (a[2][1] * a[3][2] - a[2][2] * a[3][1]) % p;
  d[1][2] = (a[3][2] * a[1][3] - a[1][2] * a[3][3]) % p;
  d[2][2] = (a[1][1] * a[3][3] - a[1][3] * a[3][1]) % p;
  d[3][2] = (a[1][2] * a[3][1] - a[1][1] * a[3][2]) % p;
  d[1][3] = (a[1][2] * a[2][3] - a[1][3] * a[2][2]) % p;
  d[2][3] = (-1 * a[1][1] * a[2][3] + a[2][1] * a[1][3]) % p;
  d[3][3] = (a[2][2] * a[1][1] - a[1][2] * a[2][1]) % p;
  delta = a[1][1] * (a[2][2] * a[3][3] - a[3][2] * a[2][3]);
  delta -= a[1][2] * (a[2][1] * a[3][3] - a[3][1] * a[2][3]);
  delta += a[1][3] * (a[2][1] * a[3][2] - a[3][1] * a[2][2]);
  delta %= p;
  z3 = f(delta, p);
  cout << (delta * z3) % p << endl;
  if (!delta == 0)
    cout << "delta = " << delta << endl;
  else
  {
    cout << "viberete drugie kluchi" << endl;
    cout << "delta = " << delta << endl;
  }
  cout << "delta^-1 = " << z3 << endl;
  for (int i = 0; i < len; i++)
  {
    mas[i] = s[i];
    cout << i << "\t" << s[i] << "\t" << mas[i] << endl;
  }
  int k = 0;
  cout << "*****************************shifr*******************" << endl;
  for (int i = 1; i <= len; i++)
  {
    if (i % 3 == 1)
    {
      x = mas[i - 1];
      k++;
    }
    else if (i % 3 == 2)
    {
      y = mas[i - 1];
      k++;
    }
    else if (i % 3 == 0)
    {
      z = mas[i - 1];
      k++;
    }
    if (k % 3 == 0)
    {
      shifr[1][k / 3] = (a[1][1] * x + a[1][2] * y + a[1][3] * z + b[1]) % p;
      shifr[2][k / 3] = (a[2][1] * x + a[2][2] * y + a[2][3] * z + b[2]) % p;
      shifr[3][k / 3] = (a[3][1] * x + a[3][2] * y + a[3][3] * z + b[3]) % p;
      cout << shifr[1][k / 3] << "\t" << shifr[2][k / 3] << "\t" << shifr[3][k / 3] << endl;
    }
  }
  cout << "******************************deshifr*********************" << endl;
  for (int i = 1; i <= len / 3; i++)
  {
    x = (z3 * (d[1][1] * (shifr[1][i] - b[1]) + d[1][2] * (shifr[2][i] - b[2]) + d[1][3] * (shifr[3][i] - b[3]))) % p;
    y = (z3 * (d[2][1] * (shifr[1][i] - b[1]) + d[2][2] * (shifr[2][i] - b[2]) + d[2][3] * (shifr[3][i] - b[3]))) % p;
    z = (z3 * (d[3][1] * (shifr[1][i] - b[1]) + d[3][2] * (shifr[2][i] - b[2]) + d[3][3] * (shifr[3][i] - b[3]))) % p;
    x %= p;
    y %= p;
    z %= p;
    if (x < 0) x += p;
    if (y < 0) y += p;
    if (z < 0) z += p;
    mas0[0][i] = x;
    mas0[1][i] = y;
    mas0[2][i] = z;
    cout << x << "\t" << y << "\t" << z << endl;
  }
  cout << "*****************************pause*******************" << endl;
  for (int i = 1; i < len / 3; i++)
  {
    cout << char(mas0[0][i]) << endl;
    cout << char(mas0[1][i]) << endl;
    cout << char(mas0[2][i]) << endl;
  }
  return 0;
}

int f(int t, int p)
{
  int z0 = 0;
  for (int i = 1; i <= p - 1; i++)
  {
    if ((i * t) % p == 1) z0 = i;
  }
  return z0;
}