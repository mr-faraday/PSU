/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №4
 * Задание 4
 * Оператор мобильной связи организовал базу данных абонентов, содержащую сведения о телефонах, их владельцах и используемых тарифах, в виде бинарного дерева. Составьте программу, которая:
    + обеспечивает начальное формирование базы данных в виде бинарного дерева;
    + производит вывод всей базы данных;
    + производит поиск владельца по номеру телефона;
    + выводит наиболее востребованный тариф (по наибольшему числу абонентов).
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

#include <map>
#include "..\task-1\Binary_Tree.h"

struct Subscriber {
  std::wstring
    name,
    phone,
    tariff;

  friend std::wostream& operator << (std::wostream& out, Subscriber& sub) {
    out << sub.name << L"   tel.";
    out << sub.phone << L"   tar.";
    out << sub.tariff;

    return out;
  }
};

std::wstring mostUT(Binary_Tree<Subscriber>& subs);

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Binary_Tree<Subscriber> subs;
  // Заполнение
  {
    subs.insert({ L"Jhon", L"2548548", L"smart" }, 1);
    subs.insert({ L"Alex", L"8717561", L"lite" }, 2);
    subs.insert({ L"Xandria", L"4828163", L"lite" }, 3);
    subs.insert({ L"Quantrell", L"4034564", L"smart" }, 4);
    subs.insert({ L"Bethany", L"4828935", L"abs" }, 5);
    subs.insert({ L"Henrik", L"4268439", L"lite" }, 6);
    subs.insert({ L"Olivia", L"1173710", L"abs" }, 7);
    subs.insert({ L"Landon", L"1366014", L"smart" }, 8);
    subs.insert({ L"Jaxon", L"0629086", L"abs" }, 9);
    subs.insert({ L"Iver", L"0334624", L"lite" }, 10);
    subs.insert({ L"Porter", L"4221323", L"smart" }, 11);
    subs.insert({ L"Enzo", L"6016150", L"abs" }, 12);
    subs.insert({ L"Leonel", L"2302277", L"smart" }, 13);
    subs.insert({ L"Bethany", L"0176414", L"smart" }, 14);
    subs.insert({ L"Vica", L"3697932", L"abs" }, 15);
    subs.insert({ L"Vermont", L"3314926", L"lite" }, 16);
    subs.insert({ L"Henry", L"6648321", L"smart" }, 17);
    subs.insert({ L"Kolton", L"3897045", L"lite" }, 18);
    subs.insert({ L"Caden", L"1520946", L"abs" }, 19);
    subs.insert({ L"Ofelia", L"8778030", L"smart" }, 20);
    subs.insert({ L"Laura", L"9453766", L"abs" }, 21);
    subs.insert({ L"Anthony", L"4685140", L"lite" }, 22);
    subs.insert({ L"Alexander", L"0239692", L"lite" }, 23);
    subs.insert({ L"Savannah", L"7928234", L"smart" }, 24);
    subs.insert({ L"Price", L"8965536", L"lite" }, 25);
    subs.insert({ L"Omega", L"9560063", L"smart" }, 26);
  }

  subs.printTree();
  wchar_t c = 0;
  while (c != L'e') {
    system("cls");
    subs.printTree();
    out << L"Most useable tarrif: " << mostUT(subs) << L"\n\r\n\r";

    out << L"Search(S) or Exit(E)? ";
    c = _getwch();
    if (c == L's') {
      std::wstring phone;
      out << L"\n\r";
      out << L"Enter phone number: ";
      in >> phone;

      for (size_t i = subs.getMinKey(); i <= subs.getMaxKey(); i++)
        if (subs.isNode(i))
          if (subs.getData(i).phone == phone) {
            out << subs.getData(i).name << L" ";
            break;
          }
      _getwch();
    }
  }

  return 1;
}

std::wstring mostUT(Binary_Tree<Subscriber>& subs) {
  std::map<std::wstring, size_t> tariffs;
  std::map<std::wstring, size_t>::iterator max, it = tariffs.begin();
  for (size_t i = subs.getMinKey(); i <= subs.getMaxKey(); i++)
    if (subs.isNode(i)) {
      if ((it = tariffs.find(subs.getData(i).tariff)) == tariffs.end()) {
        it = tariffs.begin();
        tariffs.insert(it, { subs.getData(i).tariff, 1 });
      } else it->second++;
    }

  it = tariffs.begin();
  max = tariffs.begin();
  while (it != tariffs.end()) {
    if (it->second > max->second) max = it;
    it++;
  }

  return max->first;
}
