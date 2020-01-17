/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №7
 * Задание 2(10 вар.)
 * В данном задании необходимо осуществить обработку бинарного файла(или файлов) согласно условию варианта. Имя файла передается в параметрах командной строки, а если оно там не указано, то вводится с клавиатуры. При выполнении заданий реализовать программу генерации исходного файла.
 * Дан файл, содержащий целые числа (тип int). Вычислить сумму всех чисел, являющихся числом два в целочисленной степени (1,2,4,8,...).
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Rus");

  char file_name[260];
  int choise = 0;
  FILE *file = NULL;

  int
    result = 0,
    numb = 0,
    *pointer;
  pointer = &numb;

  if (argv[1]) strcpy(file_name, argv[1]);

  while (choise != 'q') {
    printf("\n\nСгенерировать файл(G) Считать файл(R) Выход(Q)\n");
    choise = getch();

    if (choise == 'g') {
      file = NULL;
      if (argv[1]) {
        printf("\nФайл, введеный в аргуметах командной строки будет перезаписан(если он существует)\n");
        printf("Продолжить?\nВведите N для отмены, любую клавишу для продолжения");
        if (getch() == 'n') {
          printf("\n");
          continue;
        }
        printf("\n");
      }

      file = fopen(file_name, "wb");
      if (!file) {
        printf("\nВведите имя файла:\n");
        gets(file_name);
        file = fopen(file_name, "wb");
      }

      printf("Введите ряд целых чисел:\n");
      int
        numb,
        *pointer;

      if (scanf("%d", &numb) != 1) exit(0);
      while (!feof(stdin)) {
        pointer = &numb;
        fwrite(pointer, sizeof (int), 1, file);
        if (getchar() == '\n') break;
        if (scanf("%d", &numb) != 1) exit(0);
      }
      fflush(stdin);

      printf("Файл сгенерирован!\n");

      fclose(file);
    }

    if (choise == 'r') {
      file = NULL;
      if (!file) file = fopen(file_name, "rb");
      if (!file) {
        printf("\nВведите имя файла: ");
        gets(file_name);
        file = fopen(file_name, "rb");

        while (!file) {
          printf("Попробуйте еще: ");
          gets(file_name);
          file = fopen(file_name, "rb");
        }
      }

      result = 0;
      numb = 0;

      rewind(file);
      while (!feof(file)) {
        fread(pointer, sizeof (int), 1, file);
        if (fmod(log2(numb), 1) == 0) result += numb;
      }

      fclose(file);

      printf("\nCумма  чисел, являющихся числом два в целочисленной степени равна: %d\n", (int) result);
    }

  }

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}
