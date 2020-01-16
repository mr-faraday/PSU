/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №6
 * Задание 1
 * Сформировать бинарное дерево с помощью генератора случайных чисел. Вывести его с помощью метода симметричного обхода. Написать универсальную подпрограмму удаления вершины дерева вне зависимости от ее местоположения по заданному с клавиатуры ключу. Вывести на экран результирующее бинарное дерево.
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

#include "..\..\sadp_lab-4\task-1\Binary_Tree.h"

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Binary_Tree<bool> nums;
  for (int i = 0; i < 10; i++)
    nums.insert(true, rand()%100);
  nums.printTree();

  out << L"Введите ключ для удаления: ";
  int delKey;
  in >> delKey;
  nums.deleteNode(delKey);
  nums.printTree();
  
  return 1;
}
