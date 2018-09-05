 /* Ляхович Д.А.
  * 17-ХТз
  * Вариант 10
  *
  * Языки программирования
  * Лабораторная №3
  * Задание 1(40 вар.)
  * Разработать программу согласно варианту задания. Ввод и вывод массива осуществлять в одну строку.
  * Задан вещественный массив размера N. Отсортировать массив в порядке возрастания значений дробной части его элементов. Пример: 2.15 3.1 4.05 5.25 6.2 7.3 -> 4.05 3.1 2.15 6.2 5.25 7.3
  */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  setlocale(LC_ALL, "Rus");

  int n;
  printf("Введите длину массива: ");  // Приглашение к вводу значения
  if (scanf("%d", &n) != 1) exit(0);  // Ввод длины массива
  fflush(stdin);

  double arr[n];  // Создание массива вещественного типа
  printf("Введите элементы массива через пробел(дробные числа): ");
  for (int i = 0; i < n; i++)
    if (scanf("%lf", &arr[i]) != 1) exit(0);
  fflush(stdin);

  for(int i = 0; i < n - 1; i++) {
    for(int j = 0; j < n - i - 1; j++) {
      if(fmod(arr[j], 1) > fmod(arr[j+1], 1)) {
        double tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }
    }
  }

  for(int i = 0; i < n; i++) printf("%lf ", arr[i]);
  printf("\n");

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}
