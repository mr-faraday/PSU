/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №3
 * Задание 3
 * Заполнить список на заданное количество элементов случайными числами. Отсортировать список по возрастанию либо убыванию. Предоставить возможность после сортировки вывода изначального введенного списка.
 */

// Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <list>

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  std::list<int> first, second;
  std::wcout << L"Enter list length: ";
  size_t listLength;
  std::wcin >> listLength;
  
  std::list<int>::iterator it = first.begin();
  for (size_t i = 0; i < listLength; i++) {
    first.insert(it, rand());
  }

  second = first;
  second.sort();

  it = second.begin();
  while (it != second.end()) {
    std::wcout << *it << L"\n\r";
    it++;
  }

  std::wcout << L"Show initial list(Y/N)? ";
  if (_getwch() == L'y') {
    std::wcout << L"\n\r";
    it = first.begin();
    while (it != first.end()) {
      std::wcout << *it << L"\n\r";
      it++;
    }
  }

  return 1;
}
