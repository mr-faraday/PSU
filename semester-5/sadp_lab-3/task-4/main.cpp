/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №3
 * Задание 4
 * С помощью списка реализовать программу «Считалочка». N ребят расположены по кругу. Начав отсчет от первого, удаляют каждого k-ого, смыкая при этом круг. Определить порядок удаления ребят из круга. Эту задачу необходимо исследовать для различных значений N от 1 до 64, составив таблицу оставшихся ребят (t – номер оставшегося ребенка).
 */

 // Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <list>
#include <string>

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  std::list<int> guys;
  std::wcout << L"Количество ребят: ";
  size_t guysQuantity;
  std::wcin >> guysQuantity;

  std::wcout << L"Убрать каждого: ";
  size_t deleteEvery;
  std::wcin >> deleteEvery;

  if (guysQuantity == 0 || deleteEvery == 0) return 0;

  std::list<int>::iterator it = guys.begin();
  for (size_t i = 1; i <= guysQuantity; i++) guys.insert(it, i);

  std::wstring deletionSequence;
  it = guys.begin();
  int counter = 1;
  while (!guys.empty()) {
    if (counter % deleteEvery == 0) {
      deletionSequence += std::to_wstring(*it);
      deletionSequence += L"  ";
      it = guys.erase(it);
    } else it++;
    counter++;
    if (it == guys.end() && !guys.empty()) it = guys.begin();
  }

  std::wcout << deletionSequence << L"\n\r";

  std::wcout << L"N  :  t" << L"\n\r";
  for (size_t i = 1; i <= 64; i++) {
    guys.clear();
    std::list<int>::iterator it = guys.begin();
    for (size_t  j = 1; j <= i; j++) guys.insert(it, j);

    it = guys.begin();
    counter = 1;
    while (!guys.empty()) {
      if (counter % deleteEvery == 0)
        it = guys.erase(it);
      else
        it++;
      counter++;
      if (it == guys.end() && !guys.empty()) it = guys.begin();
      if (guys.size() == 1) break;
    }
    std::wcout << i << L" : " << *it << L"\n\r";
  }
  

  return 1;
}