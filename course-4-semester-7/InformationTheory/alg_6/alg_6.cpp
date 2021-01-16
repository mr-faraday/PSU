#include <iostream>
#include <string>

using namespace std;

const int n = 10;
const int p = 257;
const int len = 46;
const int kk = n / 2;

int a, b, x, z0, z1;
int shifr[3][len + 1], aa;
string s;
int mas[len + 2];

int factor(int x, int i, int p);
int factorial(int x, int i, int p);
int f3(int t, int p);

int main()
{
  s = "Undergraduate of Polotsk State University 2020";

  s += string(len - s.length(), ' '); // наращиваем строку до len

  for (int i = 0; i < len; i++)
  {
    mas[i] = s[i];
    cout << s[i] << "\t" << mas[i] << endl;
  }

  for (int j = 0; j < len; j++)
  {
    x = mas[j];
    a = 1, aa = 11;
    for (int i = 0; i <= kk - 1; i++)
    {
      z0 = factor(x, 2 * i + 1, p);
      a = (a + z0) % p;
    }
    shifr[0][j] = a;
    b = 1;
    for (int i = 0; i <= kk; i++)
    {
      z0 = factor(x, 2 * i + 1, p);
      b = (b + z0) % p;
    }
    shifr[1][j] = b;
    z0 = factorial(x, 2 * kk + 1, p);
    shifr[2][j] = (z0 * aa) % p;
    cout << shifr[0][j] << "\t" << shifr[1][j] << "\t" << shifr[2][j] << endl;
  }
  for (int j = 0; j < len; j++)
  {
    a = shifr[1][j] - shifr[0][j];
    z0 = f3(shifr[2][j], p);
    b = (z0 * a * aa) % p;
    if (b < 0) b += p;
    cout << b << "\t" << char(b) << endl;
  }
  return 0;
}

int factor(int x, int i, int p)
{
  int z = 1;
  for (int k = 1; k <= i; k++)
    z = (z * x) % p;
  int z1 = 1;
  for (int k = 1; k <= i; k++)
    z1 = (z1 * k) % p;
  int z0 = f3(z1, p);
  z0 = (z0 * z) % p;
  return z0;
}

int factorial(int x, int i, int p)
{
  int z = 1;
  for (int k = 1; k <= i - 1; k++)
    z = (z * x) % p;
  int z1 = 1;
  for (int k = 1; k <= i; k++)
    z1 = (z1 * k) % p;
  int z0 = f3(z1, p);
  z0 = (z0 * z) % p;
  return z0;
}

int f3(int t, int p)
{
  int z0 = 0;
  for (int i = 1; i <= p - 1; i++)
    if ((i * t) % p == 1) z0 = i;
  return z0;
}
