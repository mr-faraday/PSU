/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Объектно-ориентированные технологии программирования и стандарты проектирования
 * Лабораторная №2
 * Задание 1
 * Порядок выполнения работы.
 *  1. Определить иерархию классов (место, область, город, мегаполис).
 *  2. Определить в классе статическую компоненту - указатель на начало связанного списка объектов и статическую функцию для просмотра списка.
 *  3. Реализовать классы.
 *  4. Написать демонстрационную программу, в которой создаются объекты различных классов и помещаются в список, после чего список просматривается.
 *  5. Сделать соответствующие методы не виртуальными и посмотреть,
что будет.
 *  6. Реализовать аналог на языке С# и Java.
 */

 // Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Domain.h"
#include "Metropolis.h"
#include "City.h"
#include "Place.h"

Domain* Domain::listStart = nullptr;

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Domain dom1 = Domain(L"Columbia");
  Domain dom2 = Domain(L"Alaska");
  Domain dom3 = Domain(L"Washington");
  Domain dom4 = Domain(L"Wisconsin");
  Domain dom5 = Domain(L"Georgia");
  Metropolis metro1 = Metropolis(L"Highway");
  Metropolis metro2 = Metropolis(L"Brooklin");
  City city1 = City(L"New York");
  Place bridge1 = Place(L"Golden Gate");

  Domain::showList();

  return 1;
}
