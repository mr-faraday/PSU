/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №4
 * Задание 2(25 вар.)
 * Разработать программу согласно варианту задания. Максимальная длина строк не менее 80 символов. При реализации программы необходимо использовать функции для обработки строк из библиотек stdlib.h и string.h
 * Задана строка, содержащая целые и вещественные числа. Число считается целым, если у него нулевая дробная часть. Сформировать две строки, первая из которых будет содержать только вещественные числа, а вторая – только целые в том же порядке следования, что и исходной строке.
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {
  setlocale(LC_ALL, "Rus");

  char str[42000];
  printf("Введите строку: ");
  gets(str);

    // Подсчет количества чисел
  int quantity = 0;
  for (int i = 0; str[i] != '\0'; i++)
    if ((str[i] != ' ' && str[i-1] == ' ') || (str[i] != ' ' && i == 0)) ++quantity;

    // Самое длинное чсло
  char *s;
  int
    longest = 0,
    counter = 0;
  s = str;
  while (*s) {
    if (*s++ == ' ') counter = 0;
      else counter++;
    if (longest < counter) longest = counter;
  }

    // Заносим строку в матрицу
  char nums[quantity][longest+1];
  int curr_num = 0;
  counter = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ') nums[curr_num][counter++] = str[i];
    if (str[i] == ' ' && str[i-1] != ' ') nums[curr_num][counter++] = '\0';
    if (str[i] == ' ' && str[i+1] != ' ') {
      counter = 0;
      curr_num++;
    }
    if (str[i] != ' ' && str[i+1] == '\0') nums[curr_num][counter] = '\0';
  }

  char
    int_str[42000],
    float_str[42000],
    *ints,
    *fs;
  ints = int_str;
  fs = float_str;
  for (int i = 0; i < quantity; i++) {
    if (fmod(atof(nums[i]), 1) == 0) {
      s = nums[i];
      while (*s) *ints++ = *s++;
      *ints++ = ' ';
    } else {
      s = nums[i];
      while (*s) *fs++ = *s++;
      *fs++ = ' ';
    }
  }
  *ints = '\0';
  *fs = '\0';

  puts(int_str);
  puts(float_str);

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}
