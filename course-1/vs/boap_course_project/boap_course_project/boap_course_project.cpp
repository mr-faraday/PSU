#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <algorithm>

  // Вывод таблицы
#define TABLE_OUT               system("cls");\
                                head_out();\
                                db_out();
#define EXCEPTION(ERR)          {\
                                  system("cls");\
                                  std::cout << ERR;\
                                  _getwch();\
                                  return 0;\
                                }
#define SORTING(member, SIGN)   std::sort(db.begin(), db.end(), [](const Record& a, const Record& b) {\
                                  return a.member SIGN b.member;\
                                });

struct Record {
  std::string brand;
  std::string model;
  std::string year;
  std::string type;
  std::string shape;
  std::string price;
};

bool init();  // Инициализация программы. Зациклена в функции main(), возвращение в меню после завершения команды
int menu();  // Вывод меню и ожидание введения команды
typedef int (*command)();
command selector(int);  // Селектор команд

void head_out();  // Вывод шапки таблицы
void db_out();  // Вывод таблицы на экран
void string_out(struct Record *, unsigned int);  // Вывод одной строки
void line(const char gap = '_');  // Вывод линии

int create_recording();  // Создание записи и добавление в БД
int edit_recording();  // Изменение записи
int delete_recording();  // Удаление записи
int sort_db();  // Меню сортировки, выбор поля и направления
int search();  // Поиск по ДБ
int filter();  // Отфильтрованный вывод
int save();  // Сохранение БД в бинарный файл
int open();  // Открытие бинарного файла и запись его в БД
int quit();  // Выход из программы

void corr_in(std::string *, unsigned int);  // Ввод с коррекцией длины
void sorting(wchar_t *, wchar_t *);  // Сортировка БД по выбранному полю и порядку
bool is_there(std::string *, int);  // Проверка наличия ключевого слова
void size_t_input(size_t&);  // Безопасный ввод чисел

void bin_string_write(std::ostream&, std::string *);  // Запись строки в бинарный файл
void bin_string_read(std::istream&, std::string *);  // Считывание строки из бинарного файла

std::vector<Record> db;
bool cont = true;
bool is_saved = true;

int main() {
  SetConsoleTitle(L"База данных гитар");
    // Растягиваем окно
  COORD coord;
  SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);

  SetConsoleCP(1251); // настраиваем кодировку консоли (ввод)
  SetConsoleOutputCP(1251); // (вывод)

  while (cont) cont = init();

  TABLE_OUT;
  std::cout << std::endl;
  std::cout << "Нажмите любую кнопку ... ";
  _getwch();

  return 0;
}
bool init() {
  TABLE_OUT;

  int choice = menu();
  command cmd = selector(choice);
  cmd();

  return cont;
}
int menu() {
  std::cout << std::endl;
  std::cout << "  > Создать запись (C)" << std::endl;
  std::cout << "  > Изменить запись (E)" << std::endl;
  std::cout << "  > Удалить запись (D)" << std::endl << std::endl;
  std::cout << "  > Поиск по таблице (L)" << std::endl;
  std::cout << "  > Фильтр (F)" << std::endl;
  std::cout << "  > Сортировать таблицу (K)" << std::endl << std::endl;
  std::cout << "  > Сохранить в файл (S)" << std::endl;
  std::cout << "  > Открыть файл (O)" << std::endl << std::endl;
  std::cout << "<< Выйти (Q)" << std::endl;

  int choice = 0;
  std::wstring keys = L"CcСсEeУуDdВвLlДдFfАаKkЛлSsЫыOoЩщQqЙй";
  while (keys.find(choice) == std::string::npos) choice = _getwch();

  return keys.find(choice);
}
command selector(int choice) {
  if (choice >= 0 && choice <= 3) return create_recording;
  if (choice >= 4 && choice <= 7) return edit_recording;
  if (choice >= 8 && choice <= 11) return delete_recording;
  if (choice >= 12 && choice <= 15) return search;
  if (choice >= 16 && choice <= 19) return filter;
  if (choice >= 20 && choice <= 23) return sort_db;
  if (choice >= 24 && choice <= 27) return save;
  if (choice >= 28 && choice <= 31) return open;
  if (choice >= 32 && choice <= 35) return quit;
  
  return 0;
}

void head_out() {
  for (int i = 0; i < 125; i++) std::cout << "_";
  std::cout << std::endl;
  std::cout << "| №   |";
  std::cout << " Производитель           |";
  std::cout << " Модель                |";
  std::cout << " Год изг-ия |";
  std::cout << " Тип                |";
  std::cout << " Форма              |";
  std::cout << " Цена       |";
  std::cout << std::endl;
  line();
}
void db_out() {
  for (unsigned int i = 0; i < db.size(); i++) string_out(&db[i], i + 1);
  line();
}
void string_out(struct Record *rec, unsigned int num) {
  std::cout << "|";
  std::cout << "  " << num;
  if (num < 10) std::cout << "  |";
  if (num >= 10 && num < 100) std::cout << " |";
  if (num >= 100) std::cout << "|";

  std::cout << "  " << rec->brand << "  |";
  std::cout << "  " << rec->model << "  |";
  std::cout << "  " << rec->year << "  |";
  std::cout << "  " << rec->type << "  |";
  std::cout << "  " << rec->shape << "  |";
  std::cout << "  " << rec->price << "  ";
  std::cout << "|";
  std::cout << std::endl;
}
void line(const char gap) {
  std::cout << "|";
  for (int i = 0; i < 5; i++) std::cout << gap;
  std::cout << "|";
  for (int i = 0; i < 25; i++) std::cout << gap;
  std::cout << "|";
  for (int i = 0; i < 23; i++) std::cout << gap;
  std::cout << "|";
  for (int i = 0; i < 12; i++) std::cout << gap;
  std::cout << "|";
  for (int i = 0; i < 20; i++) std::cout << gap;
  std::cout << "|";
  for (int i = 0; i < 20; i++) std::cout << gap;
  std::cout << "|";
  for (int i = 0; i < 12; i++) std::cout << gap;
  std::cout << "|";

  std::cout << std::endl;
}

int create_recording() {
  system("cls");
  Record *rec = new Record;

  std::cout << "Производитель: ";
  corr_in(&rec->brand, 21);

  std::cout << "Модель: ";
  corr_in(&rec->model, 19);

  std::cout << "Год изготовления: ";
  corr_in(&rec->year, 8);

  std::cout << "Тип: ";
  corr_in(&rec->type, 16);

  std::cout << "Форма: ";
  corr_in(&rec->shape, 16);

  std::cout << "Цена: ";
  corr_in(&rec->price, 8);

  db.push_back(*rec);
  delete rec;

  is_saved = false;
  return 0;
}
int edit_recording() {
    // Проверка на размер БД
  if (db.size() == 0) EXCEPTION("Записей нет. Нажмите любую кнопку ... ");

  TABLE_OUT;

  size_t num;
  std::cout << std::endl;
  std::cout << "Введите номер записи: ";
  size_t_input(num);

    // Проверка на ввод
  if (num > db.size() || num <= 0) EXCEPTION("Некорректный номер. Нажмите любую кнопку ... ");

  system("cls");

  std::cout << "Производитель: ";
  std::cout << db[num-1].brand << std::endl;
  std::cout << "Модель: ";
  std::cout << db[num - 1].model << std::endl;
  std::cout << "Год изготовления: ";
  std::cout << db[num - 1].year << std::endl;
  std::cout << "Тип: ";
  std::cout << db[num - 1].type << std::endl;
  std::cout << "Форма: ";
  std::cout << db[num - 1].shape << std::endl;
  std::cout << "Цена: ";
  std::cout << db[num - 1].price << std::endl;
  std::cout << std::endl;

  std::cout << "Производитель: ";
  corr_in(&db[num - 1].brand, 21);

  std::cout << "Модель: ";
  corr_in(&db[num - 1].model, 19);

  std::cout << "Год изготовления: ";
  corr_in(&db[num - 1].year, 8);

  std::cout << "Тип: ";
  corr_in(&db[num - 1].type, 16);

  std::cout << "Форма: ";
  corr_in(&db[num - 1].shape, 16);

  std::cout << "Цена: ";
  corr_in(&db[num - 1].price, 8);

  is_saved = false;
  return 0;
}
int delete_recording() {
    // Проверка на размер БД
  if (db.size() == 0) EXCEPTION("Записей нет. Нажмите любую кнопку ... ");

  TABLE_OUT;

  size_t num;
  std::cout << std::endl;
  std::cout << "Введите номер записи: ";
  size_t_input(num);
  
    // Проверка ввода
  if (num > db.size() || num <= 0) EXCEPTION("Некорректный номер. Нажмите любую кнопку ... ");

  db.erase(db.begin() + num - 1);

  is_saved = false;
  return 0;
}
int sort_db() {
    // Проверка на размер БД
  if (db.size() < 2) EXCEPTION("Сортировать нечего. Нажмите любую кнопку ... ");

  TABLE_OUT;

  std::cout << std::endl;
  std::cout << "Выберите поле для сортировки:" << std::endl;
  std::cout << "1. Производитель" << std::endl;
  std::cout << "2. Модель" << std::endl;
  std::cout << "3. Год" << std::endl;
  std::cout << "4. Тип" << std::endl;
  std::cout << "5. Форма" << std::endl;
  std::cout << "6. Цена" << std::endl << std::endl;
  std::cout << "<< Назад (B)" << std::endl;

  std::wstring keys = L"123456BbИи";
  wchar_t choice_p = 0;
  while (keys.find(choice_p) == std::wstring::npos) choice_p = _getwch();

  if (keys.find(choice_p) > 6) return 0;

  TABLE_OUT;
  std::cout << std::endl;
  std::cout << "1. По возростанию(в алфавитном порядке)" << std::endl;
  std::cout << "2. По убыванию " << std::endl << std::endl;
  std::cout << "<< Назад (B)" << std::endl;

  keys = L"12BbИи";
  wchar_t how = 0;
  while (keys.find(how) == std::wstring::npos) how = _getwch();
  if (keys.find(how) > 2) return 0;

  sorting(&choice_p, &how);

  is_saved = false;
  return 0;
}
int search() {
  if (db.size() == 0) EXCEPTION("Искать негде. Нажмите любую кнопку ... ");

  TABLE_OUT;

  std::cout << std::endl;
  std::cout << "Введите ключевое слово: ";
  std::string key;
  std::cin >> key;
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  std::vector<int> nums;

    // Поиск
  for (size_t i = 0; i < db.size(); i++)
    if (is_there(&key, i)) nums.push_back(i);

  if (nums.size() == 0) EXCEPTION("Результатов нет. Нажмите любую кнопку ... ");

  system("cls");
  std::cout << "Найденые результаты:" << std::endl << std::endl;
    // Вывод результатов
  for (int i : nums) string_out(&db[i], i + 1);

  std::cout << std::endl;
  std::cout << "Нажмите любую кнопку ... ";
  _getwch();

  return 0;
}
int filter() {
  if (db.size() == 0) EXCEPTION("Фильтровать нечего. Нажмите любую кнопку ... ");

  TABLE_OUT;

  std::cout << std::endl;
  std::cout << "Введите ключевое слово: ";
  std::string key;
  std::cin >> key;
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  std::vector<int> nums;

    // Поиск
  for (size_t i = 0; i < db.size(); i++)
    if (!is_there(&key, i)) nums.push_back(i);

  if (nums.size() == 0) EXCEPTION("Результатов нет. Нажмите любую кнопку ... ");

  system("cls");
  std::cout << "Найденые результаты:" << std::endl << std::endl;
    // Вывод результатов
  for (int i : nums) string_out(&db[i], i + 1);

  std::cout << std::endl;
  std::cout << "Нажмите любую кнопку ... ";
  _getwch();

  return 0;
}
int save() {
    // Проверка на размер БД
  if (db.size() == 0) EXCEPTION("Записей нет. Нажмите любую кнопку ... ");

  TABLE_OUT;

  std::cout << std::endl;
  std::cout << "Введите название файла: ";
  std::string file_name;
  std::cin >> file_name;
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  std::ofstream file(file_name, std::ios::binary);  // Открытие файла

  if (!file) EXCEPTION("Не удалось открыть файл. Нажмите любую кнопку ... ");

  size_t size = db.size();
  file.write((char *)&size, sizeof(size_t));  // Запись количества записей
  const char *check = "guitar_db";
  file.write((char *)check, 9);  // Запись проверочной записи
    // Запись данных
  for (unsigned int i = 0; i < db.size(); i++) {
    bin_string_write(file, &db[i].brand);
    bin_string_write(file, &db[i].model);
    bin_string_write(file, &db[i].year);
    bin_string_write(file, &db[i].type);
    bin_string_write(file, &db[i].shape);
    bin_string_write(file, &db[i].price);
  }

  file.close();
  is_saved = true;
  return 0;
}
int open() {
  system("cls");
  std::cout << "Введите название файла: ";
  std::string file_name;
  std::cin >> file_name;
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  std::ifstream file(file_name, std::ios::binary);

  if (!file) EXCEPTION("Не удалось открыть файл. Нажмите любую кнопку ... ");

  if (db.size() > 0)
    while (db.size() > 0) db.erase(db.begin());  // Очистка ДБ

  size_t size;
  file.read((char *)&size, sizeof(size_t));  // Считывание кол-ва записей
  char check[10];
  file.read((char *)check, 9);  // Считывание проверочной строки
  check[9] = '\0';
    // Сравнение проверочной строки
  if (strcmp(check, "guitar_db") != 0) {
    system("cls");
    std::cout << "Файл не является БД данного формата. Нажмите любую кнопку ... ";
    file.close();
    _getwch();

    return 0;
  }
    // Чтение всего файла
  for (unsigned int i = 0; i < size; i++) {
    Record *rec = new Record;

    bin_string_read(file, &rec->brand);
    bin_string_read(file, &rec->model);
    bin_string_read(file, &rec->year);
    bin_string_read(file, &rec->type);
    bin_string_read(file, &rec->shape);
    bin_string_read(file, &rec->price);

    db.push_back(*rec);
    delete rec;
  }

  file.close();
  return 0;
}
int quit() {
  if (!is_saved) {
    char ch = 0;
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n') {
      TABLE_OUT;

      std::cout << std::endl;
      std::cout << "База данных не сохранена, продолжить? Y/N ";
      std::string inp;

      std::cin >> inp;
      std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
      ch = inp.c_str()[0];
    }

    if (ch == 'Y' || ch == 'y') cont = false;
  } else cont = false;
  
  return 0;
}

void corr_in(std::string * out, unsigned int max) {
  std::string *str = new std::string;

  getline(std::cin, *str);

  if (str->length() <= max) {
    while (max > str->length()) *str += " ";
    *out = *str;
  }
  if (str->length() > max) {
    *out = str->substr(0, max);
  }

  delete str;
}
void sorting(wchar_t *ch, wchar_t *how) {
    // По производителю
  if (*ch == L'1')
    if (*how == L'2') SORTING(brand, > )
      else SORTING(brand, < )

    // По модели
  if (*ch == L'2')
    if (*how == L'2') SORTING(model, > )
      else SORTING(model, < )

    // По году
  if (*ch == L'3')
    if (*how == L'2') SORTING(year, > )
      else SORTING(year, < )

    // По типу
  if (*ch == L'4')
    if (*how == L'2') SORTING(type, > )
      else SORTING(type, < )

    // По форме
  if (*ch == L'5')
    if (*how == L'2') SORTING(shape, > )
      else SORTING(shape, < )

    // По цене
  if (*ch == L'6')
    if (*how == L'2') SORTING(price, > )
      else SORTING(price, < )
}
bool is_there(std::string *key, int i) {
  if (db[i].brand.find(*key) != std::string::npos) return true;
  if (db[i].model.find(*key) != std::string::npos) return true;
  if (db[i].year.find(*key) != std::string::npos) return true;
  if (db[i].type.find(*key) != std::string::npos) return true;
  if (db[i].shape.find(*key) != std::string::npos) return true;
  if (db[i].price.find(*key) != std::string::npos) return true;

  return false;
}
void size_t_input(size_t& i) {
  while (!(std::cin >> i)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
}

void bin_string_write(std::ostream& ofs, std::string *str) {
  size_t len = str->length() + 1;
  ofs.write((char *)&len, sizeof(len));
  ofs.write((char *)str->c_str(), len);
}
void bin_string_read(std::istream& ifs, std::string *str) {
  size_t len;

  ifs.read((char *)&len, sizeof(len));  // Считывание длины строки
  char *buf = new char[len];  // Создание буфера
  ifs.read(buf, len);  // Чтение строки из файла
  *str = buf;  // Запись в вектор
  delete[] buf;
}
