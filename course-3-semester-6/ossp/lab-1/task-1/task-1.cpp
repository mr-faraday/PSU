/*
  Ляхович Д.А.
  17-ИТд
  ОСиСП
  9 вариант

  Задание 2
  Создайте оконное приложение. Когда пользователь нажимает мышкой
  где угодно внутри него, программа выдаёт сообщение: «Произошла ошибка!
  Программа будет закрыта!» — и закрывается.

 */

// task-1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "task-1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                    _In_ int       nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: Разместите код здесь.

  // Инициализация глобальных строк
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_TASK1, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Выполнить инициализацию приложения:
  if (!InitInstance (hInstance, nCmdShow)) {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK1));

  MSG msg;

  // Цикл основного сообщения:
  while (GetMessage(&msg, nullptr, 0, 0)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style          = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc    = WndProc;
  wcex.cbClsExtra     = 0;
  wcex.cbWndExtra     = 0;
  wcex.hInstance      = hInstance;
  wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK1));
  wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName   = NULL;
  wcex.lpszClassName  = szWindowClass;
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_LBUTTONDOWN: {
    MessageBox(
      hWnd,
      L"Произошла ошибка!\nПрограмма будет закрыта!",
      L"Ошибка",
      MB_OK | MB_ICONERROR
    );
    PostQuitMessage(0);
    break;
  }
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
