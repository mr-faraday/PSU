/* Ляхович Д.А.
 * 17-ХТз
 * Вариант 10
 *
 * Языки программирования
 * Лабораторная №7
 * Задание 3(25 вар.)
 * Реализовать программу, которая считывает из исходного текстового файла записи определенной структуры в динамический массив. Записи в текстовом файле хранятся построчно – каждая запись в одной строке. Программа обрабатывает их и записывает в результирующий бинарный файл. Дополнительно необходимо разработать программу просмотра бинарного файла. Имя исходного файла передается в параметрах командной строки, а имя результирующего файла образуется из имени исходного файла путем замены расширения на .bin. Если в исходных данных содержится ошибка, то необходимо выводить сообщение об ошибке с указанием номера строки в файле и продолжать обработку. Выполнение данного задания оценивается в 20 баллов рейтинга.
 * Упорядочить записи по серийному номеру (направление выбирает пользователь)
 * САМОЛЕТ:
 * - серийный номер (целое восьмизначное число);
 * - марка - модель (строка 20 символов);
 * - год выпуска (целое четырехзначное число);
 * - время налета (целое число, в часах).
 * Формат ввода: [Серийный номер] [Марка] – [модель], [Год выпуска], [Время налета]
 */

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
  int serial_numb;
  char model[21];
  int year;
  int fly_time;
};
void Error(int *, FILE *, struct Record [], int *, int);
int inc(int, int);
int dec(int, int);

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Rus");

  FILE
    *file = NULL,
    *file_bin = NULL;
  int ch = 0;
  int size = 0;
  int bin_size;
  int err_counter = 0;
  while (ch != 'q') {
    printf("\n\nОтсортировать данные и сгенерировать BIN файл(S) Прочитать BIN файл(R) Выход(Q)\n");
    ch = getch();

      // Сортировка и генерация BIN файла
    if (ch == 's') {
      if (argv[1]) file = (fopen(argv[1], "r"));
        else {
          printf("Файл не задан\n");
          exit(1);
        }
      if (!file) {
        printf("Не удалось открыть файл\n");
        exit(1);
      }

        // Считывание кол-ва строк
      size = 0;
      while (!feof(file))
        if (getc(file) == '\n') size++;

      struct Record records[size];  // Объявление массива структур

        // Запись файла в массив
      rewind(file);
      long int pos = 0;
      for (int i = 0; i < size; i++) {
        pos = ftell(file);  // Позиция начала строки

          // Чтение серийного номера
        fscanf(file, "%d", &records[i].serial_numb);
        if (records[i].serial_numb == '\n') {
          Error(&i, file, records, &err_counter, 1);
          continue;
        }
        if (getc(file) != ' ' || ftell(file) != 9 + pos) {
          Error(&i, file, records, &err_counter, 0);
          continue;
        }

         // Чтение модели
       char model[21];
       fgets(model, 21, file);
       if (strchr(model, '\n') != 0) {
         Error(&i, file, records, &err_counter, 1);
         continue;
       }
       if (getc(file) != ',' || getc(file) != ' ') {
         Error(&i, file, records, &err_counter, 0);
         continue;
       }
       strcpy(records[i].model, model);

         // Чтение года выпуска
       fscanf(file, "%d", &records[i].year);
       if (records[i].year == '\n') {
         Error(&i, file, records, &err_counter, 1);
         continue;
       }
       if (getc(file) != ',' || getc(file) != ' ' || ftell(file) != 37 + pos) {
         Error(&i, file, records, &err_counter, 0);
         continue;
       }

         // Чтение времени налета
       fscanf(file, "%d", &records[i].fly_time);
       if (records[i].fly_time == '\n') {
         Error(&i, file, records, &err_counter, 1);
         continue;
       }
       if (getc(file) != '\n') {
         Error(&i, file, records, &err_counter, 0);
         continue;
       }
      }

      fclose(file);
      file = NULL;

        // Сортировка
      int ch_sort = 3;
      int (*func)(int, int);
      struct Record temp;
        // Выбор направления сортировки
      while (!(ch_sort == '1' || ch_sort == '0')) {
        printf("Отсортировать записи по возрастанию(1) или убыванию(0) сериного номера\n");
        ch_sort = getch();
      }
      if (ch_sort == '1') func = inc;
        else func = dec;

      struct Record *sorted_records[size];  // Объявление массива указателей
      for (int i = 0; i < size; i++) sorted_records[i] = &records[i];

      for (int i = 0; i < size; i++)
        for (int j = 1; j < size - i; j++)
          if (!func(sorted_records[j-1]->serial_numb, sorted_records[j]->serial_numb)) {
            temp = *sorted_records[j-1];
            *sorted_records[j-1] = *sorted_records[j];
            *sorted_records[j] = temp;
          }

        // Создание бинарного файла
      char
        bin_filename[260],
        *np;
      strcpy(bin_filename, argv[1]);
      np = strrchr(bin_filename, '.');
      strcpy(np, ".bin");
      file_bin = fopen(bin_filename, "wb");

        // Запись в бинарный файл
      bin_size = size - err_counter;
      fwrite(&bin_size, sizeof (int), 1, file_bin);
      for (int i = 0; i < size; i++) {
        if (!sorted_records[i]->serial_numb) continue;

        fwrite(&sorted_records[i]->serial_numb, sizeof (int), 1, file_bin);
        fwrite(sorted_records[i]->model, 20, 1, file_bin);
        fwrite(&sorted_records[i]->year, sizeof (int), 1, file_bin);
        fwrite(&sorted_records[i]->fly_time, sizeof (int), 1, file_bin);
      }

      printf("Файл создан!\n");

      fclose(file_bin);
      file_bin = NULL;
    }

      // Чтение BIN файла
    if (ch == 'r') {

      if (!argv[1]) {
        printf("Файл не задан\n");
        exit(1);
      }

      char
        bin_filename[260],
        *np;
      strcpy(bin_filename, argv[1]);
      np = strrchr(bin_filename, '.');
      strcpy(np, ".bin");

      file_bin = fopen(bin_filename, "rb");

      fread(&bin_size, sizeof (int), 1, file_bin);
      char model[21];
      int
        serial,
        year,
        fly;
      for (int i = 0; i < bin_size; i++) {
        fread(&serial, sizeof (int), 1, file_bin);
        for (int i = 0; i < 20; i++)
          fread(&model[i], 1, 1, file_bin);
        fread(&year, sizeof (int), 1, file_bin);
        fread(&fly, sizeof (int), 1, file_bin);

        printf("%d %s, %d, %d\n", serial, model, year, fly);
      }

      fclose(file_bin);
      file_bin = NULL;
    }

  }

  printf("\nНажмите ENTER для выхода ...\n");

  return 0;
}

void Error(int *i, FILE *file, struct Record records[], int *err, int is_nl) {
  *err += 1;
  printf("Ошибка при чтении строки %d.\n", *i+1);
  if (!is_nl)
    while (getc(file) != '\n' && !feof(file));  // Перевод позиции на новую строку
  records[*i].serial_numb = 0;
  for (int j = 0; j < 20; j++) records[*i].model[j] = '\0';
  records[*i].year = 0;
  records[*i].fly_time = 0;
}

int inc(int a, int b) {
  if (a < b) return 1;
    else return 0;
}

int dec(int a, int b) {
  if (a > b) return 1;
    else return 0;
}
