/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №4
 * Задание 3
 * Найдите сумму элементов сбалансированного дерева, находящихся на уровне k.
 */

 // Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT); _setmode(_fileno(stdin),  _O_U16TEXT); _setmode(_fileno(stderr), _O_U16TEXT); std::wostream& out = std::wcout; std::wistream& in = std::wcin;
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "..\task-1\Binary_Tree.h"

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Binary_Tree<std::wstring> binTree;
  // Заполнение
  {
    binTree.insert(L"FireTeam", 5);
    binTree.insert(L"TeamSpeak", 3);
    binTree.insert(L"HolyShot", 7);
    binTree.insert(L"SpecOps", 10);
    binTree.insert(L"DevOps", 1);
    binTree.insert(L"LiveAction", 11);
    binTree.insert(L"SocialClub", 2);
    binTree.insert(L"Steam", 0);
    binTree.insert(L"Complex", 8);
    binTree.insert(L"PowerRangers", 4);
    binTree.insert(L"DarkSouls", 25);
    binTree.insert(L"DemonSouls", 26);
  }

  size_t level;
  out << L"Enter level: ";
  in >> level;
  out << L"Sum at level " << level << L" is " << binTree.sumAtLevel(level);

  return 1;
}
