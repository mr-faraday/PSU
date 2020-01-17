/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №2
 * Задание 1
 * Реализуйте структуру данных «дек». Напишите программу, содержащую описание дека и моделирующую работу дека, реализовав все указанные здесь методы. Программа считывает последовательность команд и в зависимости от команды выполняет ту или иную операцию. После выполнения каждой команды программа должна вывести одну строчку.
 */

 // Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <string>
#include <sstream>

#include "Deque.h"

int option(std::wstring&);

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  Deque<int> dq;
  
  std::wstring cmd;
  std::wstring operation;
  int parm;

  while (true) {
    std::wcout << L"[help] Command: ";
    std::getline(std::wcin, cmd);

    std::wstring operation;
    std::wistringstream(cmd) >> operation >> parm;
    
    switch (option(operation)) {
    // push_front
    case 1: {
      dq.pushFront(parm);
      std::wcout << L"ok";
      break;
    }
    // push_back
    case 2: {
      dq.pushBack(parm);
      std::wcout << L"ok";
      break;
    }
    // pop_front
    case 3: {
      if (!dq.empty()) {
        int el = dq.popFront();
        std::wcout << el;
      } else
        std::wcout << L"error";
      break;
    }
    // pop_back
    case 4: {
      if (!dq.empty()) {
        int el = dq.popBack();
        std::wcout << el;
      } else
        std::wcout << L"error";
      break;
    }
    // front
    case 5: {
      if (!dq.empty()) {
        int el = dq.getFront();
        std::wcout << el;
      } else
        std::wcout << L"error";
      break;
    }
    // back
    case 6: {
      if (!dq.empty()) {
        int el = dq.getBack();
        std::wcout << el;
      } else
        std::wcout << L"error";
      break;
    }
    // size
    case 7: {
      std::wcout << dq.getSize();
      break;
    }
    // clear
    case 8: {
      if (!dq.clear()) exit(1);
      std::wcout << L"ok";
      break;
    }
    // exit
    case 9: {
      std::wcout << L"BYE";
      return 1;
    }
    // help
    case 10: {
      std::wcout << L"Commands:\r\n";
      std::wcout << L"push_front [value]\r\n";
      std::wcout << L"push_back [value]\r\n";
      std::wcout << L"pop_front\r\n";
      std::wcout << L"pop_back\r\n";
      std::wcout << L"front\r\n";
      std::wcout << L"back\r\n";
      std::wcout << L"size\r\n";
      std::wcout << L"clear\r\n";
      std::wcout << L"exit\r\n";

      break;
    }
    default:
      break;
    }
    cmd.clear();
    std::wcout << "\n\r";
  }

  return 1;
}

int option(std::wstring& op) {
  if (op == L"push_front") return 1;
  if (op == L"push_back") return 2;
  if (op == L"pop_front") return 3;
  if (op == L"pop_back") return 4;
  if (op == L"front") return 5;
  if (op == L"back") return 6;
  if (op == L"size") return 7;
  if (op == L"clear") return 8;
  if (op == L"exit") return 9;
  if (op == L"help") return 10;

  return 0;
}
