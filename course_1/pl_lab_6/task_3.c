/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №6
 * Задание 3(10 вар.)
 * Необходимо разработать программу согласно варианту задания. При реализации функции использовать механизм передачи неопределенного числа параметров. В главной функции main реализовать демонстрацию работы разработанной функции с различным числом параметров.
 * Реализовать функцию поиска максимального четного значения, среди переданных в качестве параметров целых чисел.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

int max_even(int, ...);

int main(void) {
  setlocale(LC_ALL, "Rus");

  printf("Введите 5 целых числе в одну строку: ");
  int var1, var2, var3, var4, var5;
  if (scanf("%d", &var1) != 1) exit(0);
  if (scanf("%d", &var2) != 1) exit(0);
  if (scanf("%d", &var3) != 1) exit(0);
  if (scanf("%d", &var4) != 1) exit(0);
  if (scanf("%d", &var5) != 1) exit(0);
  fflush(stdin);

  int max = max_even(5, var1, var2, var3, var4, var5);

  if (max == -1 || max == 0)
    printf("\nЧетных чисел нет.\n");
  else
    printf("\nМаксимальное четное число: %d\n", max);

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}

int max_even(int n, ...) {
  va_list ap;
  int i = 0;
  int max = -1;
  va_start(ap, n);

  while(i < n) {
    int var = va_arg(ap, int);
    if (var % 2 == 0 && var > max) max = var;
    i++;
  }

  va_end(ap);
  return max;
}
