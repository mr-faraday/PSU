/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №2
 * Задание 3(10 вар.)
 * Разработать программу согласно варианту задания. При реализации программы использовать операторы циклов (for, while, do…while).
 * Даны два целых числа: А и В. Вывести все целые числа, расположенные между числами А и В в порядке возрастания.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>

int main(void) {
  setlocale(LC_ALL, "Rus");

  int a, b;
  printf("Введите A(целое число): ");
  if (scanf("%d", &a) != 1) exit(0);
  fflush(stdin);
  printf("Введите B(целое число): ");
  if (scanf("%d", &b) != 1) exit(0);
  fflush(stdin);

  while (a != b) {
    (a > b) ? printf("%d\n", ++b) :
      printf("%d\n", ++a);
    if (abs(a - b) == 1) break;
  }

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}
