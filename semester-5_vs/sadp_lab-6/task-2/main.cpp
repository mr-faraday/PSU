/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №6
 * Задание 2
 * Сформировать бинарное дерево, каждая вершинами которого представляет собой структуру вида:
 *   Страна | Город | Количество жителей | Метка
 * Вывести дерево любым известным Вам методом обхода. Написать подпрограмму, определяющую является ли город «городом-миллионником» и, если да, установить в структуре соответствующую метку. Вывести полученное дерево, количество «город-миллионников» и страну, с наибольшим количеством таких городов на экран.
 */

// Консольный вывод
#define CONSOLE_OUTPUT      _setmode(_fileno(stdout), _O_U16TEXT); \
                            _setmode(_fileno(stdin),  _O_U16TEXT); \
                            _setmode(_fileno(stderr), _O_U16TEXT); \
                            std::wostream& out = std::wcout; \
                            std::wistream& in = std::wcin;
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#define STR      std::wstring

#include "..\..\sadp_lab-4\task-1\Binary_Tree.h"
#include <map>

#define MILLION_PERSON_CITY  1
struct City {
  STR country;
  STR city;
  int papulation;
  int mark;

  friend std::wostream& operator << (std::wostream& out, City& city) {
    out << L"Страна: " << city.country << L"\n\r";
    out << L"Город:      " << city.city << L"\n\r";
    out << L"Население:  " << city.papulation << L"\n\r";
    // Метки
    if (city.mark & MILLION_PERSON_CITY) out << L"метка:      Город-миллионник" << L"\n\r";

    return out;
  }
};

void isMillionPerCity(City&);

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Binary_Tree<City> cities;
  // Заполнение дераева
  {
    cities.insert({ L"Belarus", L"Polotsk", 45478, 0 }, 0);
    cities.insert({ L"Poland", L"Vilnus", 574265, 0 }, 1);
    cities.insert({ L"USA", L"New York", 8145658, MILLION_PERSON_CITY }, 2);
    cities.insert({ L"Germany", L"Berlin", 3644589, MILLION_PERSON_CITY }, 3);
    cities.insert({ L"Russia", L"Moscow", 12506587, MILLION_PERSON_CITY }, 4);
    cities.insert({ L"Australia", L"Canberra", 410199, 0 }, 5);
    cities.insert({ L"Belarus", L"Minsk", 2574985, MILLION_PERSON_CITY }, 6);
    cities.insert({ L"Belarus", L"Orsha", 365214, 0 }, 7);
    cities.insert({ L"Belarus", L"Brest", 265147, 0 }, 8);
    cities.insert({ L"Belarus", L"Mogilev", 458712, 0 }, 9);
    cities.insert({ L"Belarus", L"Vitebsk", 245874, 0 }, 10);
    cities.insert({ L"USA", L"Washington", 5084816, MILLION_PERSON_CITY }, 11);
  }

  cities.printTree();

  // Подсчет городов миллионников
  std::map<STR, int> countriesMap;
  std::map<STR, int>::iterator it;
  int
    start = cities.getMinKey(),
    size = cities.getMaxKey();
  for (int i = start; i < size; i++) {
    if (!cities.isNode(i)) continue;
    City* p = &cities.getData(i);
    if ((it = countriesMap.find(p->country)) != countriesMap.end() && ((p->mark & MILLION_PERSON_CITY) == MILLION_PERSON_CITY)) {  // Если есть в словаре
      it->second++;
    } else if ((p->mark & MILLION_PERSON_CITY) == MILLION_PERSON_CITY) {  // Если нет в словаре
      countriesMap.emplace(p->country, 1);
    }
  }

  // Нахождение страны с максимальным числов городов-миллионников
  it = countriesMap.begin();
  std::map<STR, int>::iterator max = countriesMap.begin();
  while (it != countriesMap.end()) {
    if (it->second >= max->second) max = it;
    it++;
  }

  // Вывод страны
  out << L"Страна с наибольшим колличеством городов-миллионников: " << max->first << L"\n\r";


  return 1;
}

void isMillionPerCity(City& city) {
  if (city.papulation < 1000000) return;
  city.mark = city.mark | MILLION_PERSON_CITY;
}
