/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №3
 * Задание 2(40 вар.)
 * Разработать программу согласно варианту задания. Ввод и вывод массива осуществлять в одну строку. Серия – последовательность тоже серия длиной равной единице. Под удалением элементов из массива следует понимать изменение размера массива посредством изменения переменной, хранящей размер массива (например, n), а не создание нового массива. Для заданий повышенной сложности (25 баллов) использовать дополнительные массивы запрещено.
 * Задан целочисленный массив размера N. Отсортировать серии в массиве в порядке убывания их длины.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>

int main(void) {
  setlocale(LC_ALL, "Rus");

  int n;
  printf("Введите длину массива: ");
  if (scanf("%d", &n) != 1) exit(0);
  fflush(stdin);

  int arr[n];
  printf("Введите элементы массива через пробел(целые числа): ");
  for (int i = 0; i < n; i++)
    if (scanf("%d", &arr[i]) != 1) exit(0);
  fflush(stdin);

  for (int k = 0; k < n; k++) {
    int mod = 0;
    for (int i = 0; i < n; i++) {
      int
        r_zero = 0,
        r_lenght = 0,
        r_value,
        c_zero = 0,
        c_lenght = 0,
        c_value;
      for (int j = 0; j < n - mod; j++) {
        if (arr[j-1] == arr[j] && j != 0) {
          c_lenght++;
        } else {
          r_lenght = c_lenght;
          c_lenght = 1;
          r_zero = c_zero;
          c_zero = j;
          r_value = c_value;
          c_value = arr[j];
        }
      }
      if (c_lenght > r_lenght) {
        for (int k = 0; k < r_lenght; k++) {
          arr[r_zero + k] = c_value;
          arr[c_zero + c_lenght - 1 - k] = r_value;
        }
        mod += r_lenght;
      } else if (r_lenght == 0) {
        break;
      } else if (c_lenght <= r_lenght) {
        mod += c_lenght;
      }
    }

    int
      max_zero,
      max_lenght = 1,
      c_zero = 0,
      c_lenght = 1;
    for (int j = 0; j < n; j++) {
      if (arr[j-1] == arr[j] && j != 0) {
        c_lenght++;
      } else {
        if (max_lenght <= c_lenght && max_lenght != 0) {
          max_lenght = c_lenght;
          max_zero = c_zero;
        }
        c_lenght = 1;
        c_zero = j;
      }
    }

    if (max_zero == 0) break;
  }

  printf("\n");
  for(int i = 0; i < n; i++) printf("%d ", arr[i]);
  printf("\n");

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}
