/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №1
 * Задание 1
 * Разработать программу согласно варианту задания. Необходимо реализовать следующие функции для работы с динамической очередью(последовательного или связного хранения):
 *  • создание очереди;
 *  • добавление элемента в очередь;
 *  • удаление элемента из очереди;
 *  • вывод очереди на экран;
 *  • очистка очереди.
 * Используя разработанные функции выполнить обработку N очередей (число N вводит пользователь).
 * Поменять местами минимальные и первый элементы очереди.
 */

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

struct queue {
  int num = NULL;  // Число в очереди
  queue *first = nullptr;  // Первый в очереди
  queue *next = nullptr;  // Следующий в очереди
};

int init();  // Инициализация программы
int menu();  // Меню программы
typedef void (*command)();
command selector(int);  // Селектор команд

void create_queue();  // Создание новой очереди
void add_rec_to_queue();  // Добавление элемента в очередь
void delete_rec_from_queue();  // Удалить запись из очереди
void show_queue();  // Вывести очередь
void drop_queue();  // Удалить очередь
void process_queues();  // Обработать очередь
void quit();  // Выход

queue *add(queue *, int);  // Добавление записи в очередь
void deleting_queue(queue *);  // Удаление очереди

bool is_cont = true;
std::vector<queue *> queues;  // Хранилище очередей

int main()
{
  SetConsoleTitle(L"Лабораторная №1. Очередь");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_ALL, ".1251");

  while (init());
  for (queue *q : queues) deleting_queue(q);
  
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
  std::cout << " > Создать очередь (C)" << std::endl;
  std::cout << " > Добавить запись в очередь (A)" << std::endl;
  std::cout << " > Удалить элемент из очереди (R)" << std::endl;
  std::cout << " > Вывести очередь на экран (S)" << std::endl;
  std::cout << " > Очистить очередь (D)" << std::endl;
  std::cout << " > Обработать очереди (P)" << std::endl << std::endl;
  std::cout << "<< Выйти (Q)" << std::endl;

  int choice = 0;
  std::wstring keys = L"CcСсAaФфRrКкSsЫыDdВвPpЗзQqЙй";
  while (keys.find(choice) == std::wstring::npos) choice = _getwch();  // Выбор пункта меню

  return keys.find(choice);
}
command selector(int ch) {
  if (ch >= 0 && ch <= 3) return create_queue;
  if (ch >= 4 && ch <= 7) return add_rec_to_queue;
  if (ch >= 8 && ch <= 11) return delete_rec_from_queue;
  if (ch >= 12 && ch <= 15) return show_queue;
  if (ch >= 16 && ch <= 19) return drop_queue;
  if (ch >= 20 && ch <= 23) return process_queues;
  if (ch >= 24 && ch <= 27) return quit;
}

void create_queue() {
  system("cls");

  queue *q = new queue;  // Создание новой очереди
  q->first = q;
  std::cout << " Введите через пробел элементы очереди(целые числа)" << std::endl;

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
    q = add(q, i);  // Добавление элемента
  }
  queues.push_back(q);  // Добавление очереди в хранилище
}
void add_rec_to_queue() {
  system("cls");

  size_t num;
  std::cout << " В какую очередь добавить запись? ";
  while (!(std::cin >> num)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  if (num > queues.size() || num < 1) {
    system("cls");

    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  if (queues[num - 1] == nullptr) {
    queues[num - 1] = new queue;
    queues[num - 1]->first = queues[num - 1];
  }

  queue *last = queues[num - 1];
  int number;
  std::cout << " Введите целое число: ";
  while (!(std::cin >> number)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  
  queues[num - 1] = add(last, number);
}
void delete_rec_from_queue() {
  system("cls");

  size_t q_num;
  std::cout << " Из какой очереди удалить первоочередной элемент? ";
  while (!(std::cin >> q_num)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  if (q_num > queues.size() || q_num < 1) {
    system("cls");

    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  if (queues[q_num - 1] == nullptr) {
    system("cls");

    std::cout << " Queue underlow";
    _getch();

    return;
  }

  queue
    *q = queues[q_num - 1]->first,
    *curr;  // Следующий на очереди

  if (queues[q_num - 1] == queues[q_num - 1]->first) {
    delete q;
    queues[q_num - 1] = nullptr;
    return;
  }

  curr = q->next;
  curr->first = curr;
    // Объявление нового первоочередного
  while (curr->next != nullptr) {
    curr->next->first = curr->first;    
    curr = curr->next;
  }
  delete q;
}
void show_queue() {
  system("cls");

  size_t num;
  std::cout << " Введите номер очереди для вывода: ";
  while (!(std::cin >> num)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  if (num > queues.size() || num < 1) {
    system("cls");
    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  if (queues[num - 1] == nullptr) {
    system("cls");

    std::cout << " Queue underlow";
    _getch();

    return;
  }

  if (queues[num - 1] == queues[num - 1]->first) {
    std::cout << std::endl;
    std::cout << queues[num - 1]->num << std::endl;
    std::cout << std::endl << "Нажмите любую клавишу для продолжения ... ";
    _getch();
    return;
  }

  std::cout << std::endl;
  queue *head = queues[num - 1]->first;
  while (true) {
    std::cout << head->num << std::endl;
    if (head->next == nullptr) break;
    head = head->next;
  }

  std::cout << std::endl << "Нажмите любую клавишу для продолжения ... ";
  _getch();
}
void drop_queue() {
  system("cls");

  size_t num;
  std::cout << " Введите номер очереди на удаление: ";
  while (!(std::cin >> num)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  if (num > queues.size() || num < 1) {
    system("cls");
    std::cout << " Некорректный номер.";
    _getch();

    return;
  }

  deleting_queue(queues[num-1]);
  queues.erase(queues.begin() + num - 1);
}
void process_queues() {
  system("cls");

  size_t n;
  std::cout << " Сколько очередей обработать? ";
  while (!(std::cin >> n)) {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');
  }
  std::cin.ignore((std::numeric_limits<size_t>::max)(), '\n');

  if (n > queues.size() || n < 1) {
    system("cls");

    std::cout << " Некорректный номер.";
    _getch();

    return;
  }
  
    // Обработка отдельной очереди
  for (size_t i = 0; i < n; i++) {
    queue
      *min = queues[i]->first,
      *old_head = queues[i]->first,
      *q,
      *curr = queues[i]->first;

    q = queues[i];
      // Поиск минимального элемента
    while (true) {
      if (curr->num < min->num) min = curr;
      if (curr->next == nullptr) break;
      curr = curr->next;
    }

    q = new queue;
    q->first = q;
    q = add(q, min->num);  // Добавление минимального элемента
    curr = old_head->next;
    while (true) {
      if (min == curr) {
        q = add(q, old_head->num);  // Добавление первого элемента на место минимального
        curr = curr->next;
        if (curr == nullptr) break;
        continue;
      }
      q = add(q, curr->num);

      if (curr->next == nullptr) break;
      curr = curr->next;
    }
    deleting_queue(old_head);
    queues[i] = q;
  }
}
void quit() {
  is_cont = false;
}

queue *add(queue *last, int number) {
  if (last->num != NULL) {
    last->next = new queue;  // Новая запись в очередь
    last->next->first = last->first;  // Указание на "первоочередного"
    last = last->next;  // Новый "конец" очереди
    last->num = number;  // Присвоение значения

    return last;
  }
  else  last->num = number;  // Если первый в очереди
  return last;
}
void deleting_queue(queue *q) {
  if (q == nullptr) return;

  queue *to_drop;
  while (q->first != q) {
    to_drop = q->first;  // Элемент на удаление
    q->first = to_drop->next;  // Следующий на удаление
    delete to_drop;
  }

  delete q;
}