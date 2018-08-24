/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №6
 * Задание 3(10 вар.)
 * Необходимо разработать программу согласно варианту задания. При реализации использовать указатели на функции и (или) массивы указателей на функции. В заданиях с массивами или списками размер и значения элементов вводятся пользователем.
 * Дан вещественный массив. Упорядочить массив тремя способами: в порядке возрастания значений элементов; в порядке убывания дробной части элементов; в порядке возрастания суммы первых четырех разрядов дробной части элементов. В функцию сортировки должен передаваться указатель на функцию сравнения двух элементов. Способ сортировки выбирает пользователь.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

void sort(double [], int, int (*)(double, double));
int inc(double, double);
int dec(double, double);
int what(double, double);

int main(void) {
  setlocale(LC_ALL, "Rus");

  printf("Введите колличество элементов массива: ");
  int size;
  if (scanf("%d", &size) != 1) exit(0);
  fflush(stdin);

  double arr[size];
  printf("Введите элеменнты массива через пробел(дробные числа): ");
  for (int i = 0; i < size; i++)
    if (scanf("%lf", &arr[i]) != 1) exit(0);
  fflush(stdin);

  printf("\nВведите вариант сортировки:\n");
  printf("1: В порядке возрастания значений элементовю\n");
  printf("2: В порядке убывания дробной части элементов\n");
  printf("3: В порядке возрастания суммы первых четырех разрядов дробной части элементов\n");
  int type;
  if (scanf("%d", &type) != 1) exit(0);
  fflush(stdin);
  if (!(type == 1 || type == 2 || type == 3)) exit(0);

  int (*compare)(double, double) = NULL;
  switch (type) {
    case 1:
      compare = inc;
      break;
    case 2:
      compare = dec;
      break;
    case 3:
      compare = what;
      break;
  }

  sort(arr, size, compare);
  for (int i = 0; i < size; i++)
    printf("%lf ", arr[i]);
  printf("\n");

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}

void sort(double arr[], int size, int (*compare)(double, double)) {
  double temp;
  for (int i = 0; i < size; i++)
    for (int j = i + 1; j < size; j++)
      if (compare(arr[i], arr[j])) {
        temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
}

int inc(double a, double b) {
  if (a > b) return 1;
  return 0;
}

int dec(double a, double b) {
  if (fmod(a, 1) < fmod(b, 1)) return 1;
  return 0;
}

int what(double a, double b) {
  double x, y;
  modf(a * 10000, &x);
  modf(b * 10000, &y);

  int i = (int) x % 10000;
  int k = (int) y % 10000;

  i = i % 10 + (i/10 % 10) + (i/100 % 10) + (i/1000 % 10);
  k = k % 10 + (k/10 % 10) + (k/100 % 10) + (k/1000 % 10);

  if (i > k) return 1;
  return 0;
}
