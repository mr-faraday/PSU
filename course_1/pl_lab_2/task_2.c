/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №2
 * Задание 2(40 вар.)
 * Разработать программу согласно варианту задания. Типы данных определяются из специфики задачи, если их тип не указан явно. При реализации программы использовать оператор выбора switch.
 * Даны два целых числа: D (день) и M (месяц), определяющие правильную дату високосного года. Вывести значения D и M для даты, предшествующей указанной.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>

int main(void) {
  setlocale(LC_ALL, "Rus");

	int d, m;

  start:
	printf("Введите число D(натуральное число): ");
  if (scanf("%d", &d) != 1) exit(0);
  fflush(stdin);
  printf("Введите месяц M(натуральное число): ");
  if (scanf("%d", &m) != 1) exit(0);
  fflush(stdin);

  switch (d <= 0 || d >= 32 || m <= 0 || m >= 13) {
    case 1:
      printf("\nПопробуйте еще.\n\n");
      goto start;
    default:
      break;
  }

  switch (d >= 2) {
    case 1:
      printf("\n%d.%d\n", --d, m);
      break;
    case 0:
      switch (m) {
        case 1:
          printf("\n%d.%d\n", 31, 12);
          break;
        case 2:
          printf("\n%d.%d\n", 31, 1);
          break;
        case 3:
          printf("\n%d.%d\n", 29, 2);
          break;
        case 4:
          printf("\n%d.%d\n", 31, 3);
          break;
        case 5:
          printf("\n%d.%d\n", 30, 4);
          break;
        case 6:
          printf("\n%d.%d\n", 31, 5);
          break;
        case 7:
          printf("\n%d.%d\n", 30, 6);
          break;
        case 8:
          printf("\n%d.%d\n", 31, 7);
          break;
        case 9:
          printf("\n%d.%d\n", 31, 8);
          break;
        case 10:
          printf("\n%d.%d\n", 30, 9);
          break;
        case 11:
          printf("\n%d.%d\n", 31, 10);
          break;
        case 12:
          printf("\n%d.%d\n", 30, 11);
          break;
        default:
          printf("Что-то пошло не так...\n");
      }
      break;
    default:
      printf("Что-то пошло не так...\n");
  }

  printf("\nНажмите ENTER для выхода ...\n");

	return 0;
}
