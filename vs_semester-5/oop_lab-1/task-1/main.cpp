/* ������� �.�.
 * 17-���
 * ������� 8
 *
 * ��������-��������������� ���������� ���������������� � ��������� ��������������
 * ������������ �1
 * ������� 1
 * ��� ������:
 *  1. ������� ����� ����������� �������� �������� ��������(�������).
 *  2. ������� ����������� ��� ����������
 *  3. ������� ����������� � �����������
 *  4. ������� ����������
 *  5. ������� ������ ��� ������ ������ � ������ � ������ �� �������.
 *  6. ����������� ��������� �� �++, �#, Java
 *  7. * ������� ����������� ����������� ��� ������� �� ����� �++.
 */

  // ���������� �����
#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Laptop.h"

int main() {
  #ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  _getwch();

  return 1;
}
