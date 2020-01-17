/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №6
 * Задание 1(10 вар.)
 * Во всех заданиях необходимо разработать программу согласно варианту задания. В основной функции main реализовать демонстрацию работы разработанной пользовательской функции. Ввод и вывод всех данных осуществляется в функции main.
 * Разработать функцию для вычисления члена ряда: ln(n)/n!. Используя разработанную функцию вычислить сумму ряда с позиции N до позиции M.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

double row_sum(int, int);
int fact(int);

int main(void) {
  setlocale(LC_ALL, "Rus");

  printf("Введите начальную позицию(целое число): ");
  int n;
  if (scanf("%d", &n) != 1) exit(0);

  printf("Введите конечную позицию(целое число): ");
  int m;
  if (scanf("%d", &m) != 1 || n > m) exit(0);

  printf("Сумма члена ряда ln(n)/n! от позиции %d до %d равна: %lf", n, m, row_sum(n, m));

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}

double row_sum(int n, int m) {
  if (n == m) {
    return log(n)/fact(n);
  } else {
    return log(n)/fact(n) + row_sum(n + 1, m);
  }
}

int fact(int n) {
  if (n == 1) {
    return 1;
  } else {
    return n * fact(n - 1);
  }
}
