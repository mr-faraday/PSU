/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Курсовой проект
 * Разработка игровой программы «Реверси»
 * Программа должна реализовать игру «Реверси» стандартного типа для двух игроков и против компьютера. Реализовать возможность звукового сопровождения, предусмотреть возможность сохранения и последующей загрузки игры.
 */

// Консольный вывод
//#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
//#pragma comment             (linker, "/SUBSYSTEM:CONSOLE")
//#pragma comment             (linker, "/ENTRY:wWinMainCRTStartup")
//#include <conio.h>
//#include <iostream>
//#include <io.h>
//#include <fcntl.h>

#include <Windows.h>
#include "app.h"

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  #ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  return init((unsigned int) hInstance, nCmdShow);
}
