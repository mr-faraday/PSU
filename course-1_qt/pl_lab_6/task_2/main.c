/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №6
 * Задание 2(25 вар.)
 * Во всех заданиях необходимо разработать программу согласно варианту задания. При реализации функции использовать механизм передачи параметров по ссылке. В основной функции main реализовать демонстрацию работы разработанной пользовательской функции. Ввод и вывод всех данных осуществляется в функции main.
 * Реализовать функцию, осуществляющую поиск в вещественном массиве двух элементов наиболее близких друг к другу по значению. Массив и его размер передаются в качестве параметров. Функция должна вернуть позиции найденных элементов. Используя разработанную функцию осуществить поиск в N массивах, введенных пользователем.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

struct Positions {
  int firstPos;
  int secPos;
};

struct Positions search(float [], int *);

int main(void) {
  setlocale(LC_ALL, "Rus");

  printf("Введите колличество массисов: ");
  int n;
  if (scanf("%d", &n) != 1) exit(0);
  fflush(stdin);

  int poss[n][2];
  for (int i = 1; i <= n; i++) {
    printf("\nВведите колличество элементов массива %d: ", i);
    int size;
    if (scanf("%d", &size) != 1) exit(0);
    fflush(stdin);

    float arr[size];
    printf("Введите элементы массива %d через пробел(дробные числа): ", i);
    for (int j = 0; j < size; j++)
      if (scanf("%f", &arr[j]) != 1) exit(0);
    fflush(stdin);

    struct Positions result = search(arr, &size);
    poss[i][0] = result.firstPos;
    poss[i][1] = result.secPos;
  }

  for (int i = 1; i <= n; i++) printf("\nВ массиве %d минимальная разница в позициях %d и %d.", i, poss[i][0]+1, poss[i][1]+1);

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}

struct Positions search(float arr[], int *size) {
  float indexes[*size][3];
  for (int i = 0; i < *size; i++) {
    indexes[i][0] = i;
    for (int j = 0; j < *size; j++) {
      if (j == 0 && i != 0) {
        indexes[i][1] = j;
        indexes[i][2] = fabsf(arr[i] - arr[j]);
      }
      if (j == 0 && i == 0) {
        indexes[i][1] = j+1;
        indexes[i][2] = fabsf(arr[i] - arr[j+1]);
      }
      if (indexes[i][2] > fabsf(arr[i] - arr[j]) && j != i) {
        indexes[i][1] = j;
        indexes[i][2] = fabsf(arr[i] - arr[j]);
      }
    }
  }

  int min = 0;
  for (int i = 0; i < *size; i++)
    if (indexes[min][2] > indexes[i][2]) min = i;

  struct Positions result;
  result.firstPos = (int) indexes[min][0];
  result.secPos = (int) indexes[min][1];

  return result;
}
