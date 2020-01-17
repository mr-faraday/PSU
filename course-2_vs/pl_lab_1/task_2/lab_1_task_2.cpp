/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №1
 * Задание 2
 * Разработать программу согласно варианту задания. Необходимо реализовать следующие функции для работы со стеком динамического хранения (последовательного или связного):
 *  • создание стека;
 *  • добавление элемента в стек;
 *  • удаление элемента из стека;
 *  • вывод стека на экран;
 *  • очистка стека.
 * Используя разработанные функции выполнить обработку N стеков (число N вводит пользователь).
 * Дан набор из чисел. Создать два стека: первый должен содержать числа из исходного набора с нечетными номерами (1, 3, ...), а второй — с четными (2, 4, ...).
 */

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

struct stack {
  int num = NULL;  // Число в стеке
  stack *first = nullptr;  // "Дно" стека
  stack *prev = nullptr;  // Предыдущий в стеке
};

int init();  // Инициализация программы
int menu();  // Меню программы
typedef void(*command)();
command selector(int);  // Селектор команд

void create_stack();  // Создание нового стека
void add_rec_to_stack();  // Добавление элемента в стек
void delete_rec_from_stack();  // Удалить запись из стека
void show_stack();  // Вывести стек
void drop_stack();  // Удалить стек
void process_stacks();  // Обработать стек
void quit();  // Выход

stack *add(stack *, int);  // Добавление записи в стек
void deleting_stack(stack *);  // Удаление стека
void input_size_t(size_t&);
void input_int(int&);

bool is_cont = true;
std::vector<stack *> stacks;  // Хранилище стеков

int main()
{
  SetConsoleTitle(L"Лабораторная №1. Стек");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_ALL, ".1251");

  while (init());
  for (stack *s : stacks) deleting_stack(s);

  return 0;
}
int init() {
  system("cls");

  int choice = menu();
  command cmd = selector(choice);
  cmd();

  return is_cont;
}

int menu() {
  std::cout << " > Создать стек (C)" << std::endl;
  std::cout << " > Добавить запись в стек (A)" << std::endl;
  std::cout << " > Удалить элемент из стека (R)" << std::endl;
  std::cout << " > Вывести стек на экран (S)" << std::endl;
  std::cout << " > Очистить стек (D)" << std::endl;
  std::cout << " > Обработать стеки (P)" << std::endl << std::endl;
  std::cout << "<< Выйти (Q)" << std::endl;

  int choice = 0;
  std::wstring keys = L"CcСсAaФфRrКкSsЫыDdВвPpЗзQqЙй";
  while (keys.find(choice) == std::wstring::npos) choice = _getwch();  // Выбор пункта меню

  return keys.find(choice);
}
command selector(int ch) {
  if (ch >= 0 && ch <= 3) return create_stack;
  if (ch >= 4 && ch <= 7) return add_rec_to_stack;
  if (ch >= 8 && ch <= 11) return delete_rec_from_stack;
  if (ch >= 12 && ch <= 15) return show_stack;
  if (ch >= 16 && ch <= 19) return drop_stack;
  if (ch >= 20 && ch <= 23) return process_stacks;
  if (ch >= 24 && ch <= 27) return quit;
}

void create_stack() {
  system("cls");

  stack *st = new stack;  // Создание нового стека
  st->first = st;
  std::cout << " Введите через пробел элементы стека(целые числа)" << std::endl;

  int i = 0;
  std::string s;
  getline(std::cin, s);
    // Создание потка для чтения чисел из строки
  for (std::stringstream ss(s); !ss.eof();) {
    if (!(ss >> i)) {
      ss.clear();
      ss.ignore(1, '\n');  // Игнорирование поподания лишних символов
      continue;
    }
    st = add(st, i);  // Добавление элемента
  }
  stacks.push_back(st);  // Добавление стека в хранилище
}
void add_rec_to_stack() {
  system("cls");

  size_t num;
  std::cout << " В какой стек добавить запись? ";
  input_size_t(num);

  if (num > stacks.size() || num < 1) {
    system("cls");

    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  if (stacks[num - 1] == nullptr) {
    stacks[num - 1] = new stack;
    stacks[num - 1]->first = stacks[num - 1];
  }

  stack *last = stacks[num - 1];
  int number;
  std::cout << " Введите целое число: ";
  input_int(number);

  stacks[num - 1] = add(last, number);
}
void delete_rec_from_stack() {
  system("cls");

  size_t s_num;
  std::cout << " Из какого стека удалить верхний элемент? ";
  input_size_t(s_num);
  
  if (s_num > stacks.size() || s_num < 1) {
    system("cls");

    std::cout << " Некорректный номер.";
    _getch();

    return;
  }

  stack *to_del = stacks[s_num - 1];
  if (to_del == nullptr) {
    system("cls");

    std::cout << " Stack underflow ";
    _getch();

    return;
  }
  stacks[s_num - 1] = to_del->prev;  // Новая голова стека

  delete to_del;
}
void show_stack() {
  system("cls");

  size_t num;
  std::cout << " Введите номер стека для вывода: ";
  input_size_t(num);

  if (num > stacks.size() || num < 1) {
    system("cls");
    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  if (stacks[num - 1] == nullptr) {
    system("cls");

    std::cout << " Stack underflow ";
    _getch();

    return;
  }

  std::cout << std::endl;
  stack *head = stacks[num - 1];
  while (true) {
    std::cout << head->num << std::endl;
    if (head->prev == nullptr) break;
    head = head->prev;
  }

  std::cout << std::endl << "Нажмите любую клавишу для продолжения ... ";
  _getch();
}
void drop_stack() {
  system("cls");

  size_t num;
  std::cout << " Введите номер стека на удаление: ";
  input_size_t(num);

  if (num > stacks.size() || num < 1) {
    system("cls");
    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  if (stacks[num - 1] == nullptr) {
    stacks.erase(stacks.begin() + num - 1);
    return;
  }

  deleting_stack(stacks[num - 1]);
  stacks.erase(stacks.begin() + num - 1);
}
void process_stacks() {
  system("cls");

  size_t n;
  std::cout << " Сколько очередей обработать? ";
  input_size_t(n);

  if (n > stacks.size() || n < 1) {
    system("cls");

    std::cout << " Некорректный номер.";
    _getch();

    return;
  }

  std::vector<stack *> new_stacks;
    // Обработка отдельной очереди
  for (unsigned short i = 0; i < n; i++) {
    stack
      *s = new stack,
      *ptr;
    s->first = s;

      // Четные числа
    ptr = stacks[i];
    while (true) {
      if (ptr == nullptr) break;
      if (ptr->num % 2 == 0) {
        s = add(s, ptr->num);
        ptr = ptr->prev;
        continue;
      }
      ptr = ptr->prev;
    }
    new_stacks.push_back(s);  // Запись в новое хранилище четных чисел

      // Нечетные числа
    s = new stack;
    s->first = s;
    ptr = stacks[i];
    while (true) {
      if (ptr == nullptr) break;
      if (ptr->num % 2 == 1) {
        s = add(s, ptr->num);
        ptr = ptr->prev;
        continue;
      }
      ptr = ptr->prev;
    }
    new_stacks.push_back(s);  // Запись в новое хранилище не четных чисел
  }
    // Если обрабатываются не все стеки
  size_t i = n;
  while (i < stacks.size()) {
    i++;
    new_stacks.push_back(stacks[i - 1]);
  }
    // Удаление старых стеков
  for (stack *s : stacks) {
    deleting_stack(s);
    if (s = stacks[n - 1]) break;
  }

  new_stacks.swap(stacks);  // Обмен хранилищами
  new_stacks.~vector();
}
void quit() {
  is_cont = false;
}

stack *add(stack *st, int number) {
  if (st->num != NULL) {
    stack *n = new stack;  // Указатель на новую запись
    n->prev = st;  // Указание на следующий элемент в стопке
    n->num = number;  // Присвоение значения
    n->first = st->first;  // Указание на дно стека

    return n;
  }
  else  st->num = number;  // Если первый в стеке
  return st;
}
void deleting_stack(stack *s) {
  if (s == nullptr) return;
  stack *to_drop = s;
  while (s->first != s) {
    to_drop = s;  // Элемент на удаление
    s = to_drop->prev;  // Следующий на удаление
    delete to_drop;
  }

  delete s;
}
void input_size_t(size_t& i) {
  while (!(std::cin >> i)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
}
void input_int(int& i) {
  while (!(std::cin >> i)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
}