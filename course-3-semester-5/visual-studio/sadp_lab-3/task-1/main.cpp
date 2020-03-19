/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №3
 * Задание 1
 * В текстовом файле находится текст, состоящий из слов. Написать программу, создающую список, содержащий частоту упоминания в тексте каждого слова.
 */

// Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <string>
#include <sstream>
#include <map>
#include <fstream>

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  std::map<std::wstring, size_t> lib;
  std::ifstream fIn(".\\file.txt");
  if (!fIn.is_open()) {
    std::wcout << L"\n\r" << L"bad" << L"\n\r";
    return 0;
  }
  
  std::wstring file((std::istreambuf_iterator<char>(fIn)),  // Считывание файла в сторку
                  std::istreambuf_iterator<char>());
  fIn.close();
  std::wistringstream input = std::wistringstream(file);
  std::wstring toAdd;
  std::map<std::wstring, size_t>::iterator p;
  while (!input.eof()) {
    input >> toAdd;

    p = lib.find(toAdd);
    if (p == lib.end()) lib.insert(std::pair<std::wstring, int>(toAdd, 1));
    else p->second++;
    toAdd.clear();
  }

  p = lib.begin();
  while (p != lib.end()) {
    std::wcout << p->first << L" : " << p->second << L"\n\r";
    p++;
  }
  std::wcout << L"\n\r" << L"ok" << L"\n\r";

  return 1;
}