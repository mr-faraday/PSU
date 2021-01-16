#include <iostream>
#include <string>

using namespace std;

const int n = 599;
const int p = 257;
const int len = 40;

int a, b, x, y, z1, z2, z3, z4, z00;
int mas1[len + 1], mas2[len + 1], mas3[len + 1];
string s;
int mas[len + 1];

int f1(int x, int y, int n, int p, int a, int b);
int f2(int x, int y, int n, int p, int a, int b);
int f3(int t, int p);

int main()
{
  s = "Polotsk State University 1234567890";
  a = 119;
  b = 131;
  x = 1;

  s += string(len - s.length(), ' '); // наращиваем строку до len

  for (int i = 0; i < len; i++)
  {
    mas[i] = s[i];
    cout << s[i] << "\t" << mas[i] << endl;
  }

  for (int i = 0; i < len; i++)
  {
    y = mas[i];
    z2 = f1(x, y, n, p, a, b);
    if (z2 == 0)
    {
      cout << "error" << endl;
      z1 = (x + y) % p;
      z2 = (y - x) % p;
      z3 = f3(2, p);
      z4 = ((z1 + z2) * z3) % p;
      mas1[i] = z4;
      mas2[i] = 0;
    }
    else if (!z2 == 0)
    {
      z3 = f3(z2, p);
      z00 = f2(x, y, n, p, a, b);
      z4 = (z3 * z00 - x) % p;
      if (z4 < 0) z4 += p;
      mas1[i] = 0;
      mas2[i] = z4;
    }
    mas3[i] = mas1[i] + mas2[i];
    cout << "i=\t" << i << "\t" << mas3[i] << "\t" << char(mas3[i]) << endl;
  }
  return 0;
}

int f1(int x, int y, int n, int p, int a, int b)
{
  int z0 = 0, d = 1, zz = -1;
  for (int i = 1; i <= b; i++)
    d = (d * a) % p;
  for (int i = 0; i <= n - 1; i++)
  {
    int z1 = 1, z = 1;
    for (int j = 1; j <= i; j++)
      z = (z * x) % p;
    for (int j = 1; j <= n - i - 1; j++)
      z1 = (z1 * y) % p;
    zz *= -1;
    z0 = (z0 + z * z1 * zz) % p;
  }
  int z2 = (z0 * d) % p;
  if (z2 < 0) z2 += p;
  return z2;
}

int f2(int x, int y, int n, int p, int a, int b)
{
  int d = 1;
  for (int i = 1; i <= b; i++)
    d = (d * a) % p;
  int z1 = 1, z2 = 1;
  for (int i = 1; i <= n; i++)
  {
    z1 = (z1 * x) % p;
    z2 = (z2 * y) % p;
  }
  int z00 = (z2 + z1) % p;
  if (z00 < 0) z00 += p;
  z00 = (z00 * d) % p;
  return z00;
}

int f3(int t, int p)
{
  int z0 = 0;
  for (int i = 1; i <= p - 1; i++)
    if ((i * t) % p == 1) z0 = i;
  return z0;
}
