/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Структуры и алгоритмы обработки данных
 * Лабораторная №3
 * Задание 2
 * Написать программу, которая получив на выходе выражение, состоящего из переменных (одна буква), констант (одна цифра). Знаков операций (+-* /) и круглых скобок, строит ПОЛИЗ этого выражения. Использовать стек.
 */

 // Консольный вывод
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <string>
#include <stack>

int getOperatorPriority(wchar_t);

int main() {
#ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  std::stack<wchar_t> buff;
  std::wcout << L"Enter expression: ";
  std::wstring input, output;

  std::wcin >> input;
  const wchar_t* p = input.c_str();
  
  //std::wistringstream in = std::wistringstream(input);
  bool conToAdd;
  bool isOperator;
  int opPriority;
  while (*p != L'\0') {
    conToAdd =
      (*p >= L'0' && *p <= L'9') ||
      (*p >= L'A' && *p <= L'Z') ||
      (*p >= L'a' && *p <= L'z');
    isOperator = *p == L'+' || *p == L'-' || *p == L'/' || *p == L'*' || *p == L'(' || *p == L')';

    // Если переменная или число
    if (conToAdd) {
      output += *p;
      p++;
      continue;
    }

    // Если оператор
    if (isOperator) {
      opPriority = getOperatorPriority(*p);
      if (opPriority == -1) {
        buff.push(*p);
        p++;
        continue;
      }

      if (opPriority == 0 && !buff.empty()) {
        while (buff.top() != L'(') {
          output += buff.top();
          buff.pop();
        }

        buff.pop();
        p++;
        continue;
      }

      if (!buff.empty())
        while (opPriority < getOperatorPriority(buff.top())) {
          output += buff.top();
          buff.pop();
          if (buff.empty()) break;
          if (buff.top() == L'(') break;
        }

      buff.push(*p);
      p++;
      continue;
    }

    return 0;
  }
  while (!buff.empty()) {
    output += buff.top();
    buff.pop();
  }

  std::wcout << output;

  return 1;
}

int getOperatorPriority(wchar_t op) {
  if (op == L'(') return -1;
  if (op == L')') return 0;
  if (op == L'+' || op == L'-') return 1;
  if (op == L'/' || op == L'*') return 2;

  return -5;
}
