/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №4
 * Задание 1
 * Реализуйте программу, в которой выполняются все основные операции с бинарным деревом:
   + создание бинарного дерева;
   + печать бинарного дерева;
   + обход бинарного дерева;
   + вставка элемента в бинарное дерево;
   + удаление элемента из бинарного дерева;
   + проверка пустоты бинарного дерева;
   + удаление бинарного дерева.
 */

// Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT); _setmode(_fileno(stdin),  _O_U16TEXT); _setmode(_fileno(stderr), _O_U16TEXT); std::wostream& out = std::wcout; std::wistream& in = std::wcin;
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Binary_Tree.h"

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Binary_Tree<std::wstring> binTree;

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

  binTree.printTree();
  out << L"deletion: " << 5 << L"\n\r";
  binTree.deleteNode(5);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 4 << L"\n\r";
  binTree.deleteNode(4);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 7 << L"\n\r";
  binTree.deleteNode(7);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 1 << L"\n\r";
  binTree.deleteNode(1);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 10 << L"\n\r";
  binTree.deleteNode(10);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 3 << L"\n\r";
  binTree.deleteNode(3);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 8  << L"\n\r";
  binTree.deleteNode(8);
  binTree.printTree();
  out << L"\n\r";

  out << L"deletion: " << 2 << L"\n\r";
  binTree.deleteNode(2);
  binTree.printTree();
  out << L"\n\r";
  
  return 1;
}
