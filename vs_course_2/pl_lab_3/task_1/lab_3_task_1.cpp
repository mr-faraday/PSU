/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №3
 * Задание 1
 * Изначально текстовый редактор содержит значение ноль. При нажатии кнопки с цифрой в конец строки текстового редактора добавляется соответствующая цифра. При нажатии кнопки «С» строка сбрасывается в ноль. Возможность редактирования в текстовом поле должна быть запрещена. Число в текстовом поле не может иметь ведущих нулей, а его длина не может превышать 10 цифр.
 */

//#pragma comment (linker, "/SUBSYSTEM:CONSOLE")
//#pragma comment (linker, "/ENTRY:wWinMainCRTStartup")
//#include <iostream>

#include <windows.h>
#include <string>

 // Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
LPCWSTR szTitle = L"Программа (вариант 9)";     // Текст строки заголовка
LPCWSTR szWindowClass = L"Main";                // имя класса главного окна
UINT width = 300;
UINT height = 210;
UINT button_width = width / 4 - 20;
std::wstring areaValue = L"0";

HWND hMain;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
VOID                setValue(HWND, WCHAR);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
  MyRegisterClass(hInstance);

  // Выполнить инициализацию приложения:
  if (!InitInstance(hInstance, nCmdShow)) return FALSE;

  MSG msg;

  // Цикл основного сообщения:
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName = (LPCWSTR)NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  hMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
    (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1),
    (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1),
    width, height, nullptr, nullptr, hInstance, nullptr);

  if (!hMain) {
    return FALSE;
  }  

  ShowWindow(hMain, SW_SHOW);
  UpdateWindow(hMain);

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static HWND
    output_area,
    button_1,
    button_2,
    button_3,
    button_c,
    button_4,
    button_5,
    button_6,
    button_7,
    button_8,
    button_9,
    button_0;

  switch (message) {
  case WM_CREATE: {
    output_area = CreateWindow(L"edit", L"0",
      WS_CHILD | WS_VISIBLE | ES_READONLY | ES_RIGHT,
      10, 10, width - 40, 16, hWnd,
      (HMENU)0, hInst, 0);    

    button_1 = CreateWindow(L"button", L"1", WS_CHILD | WS_VISIBLE,
      10, 50,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_2 = CreateWindow(L"button", L"2", WS_CHILD | WS_VISIBLE,
      width / 4 + 3, 50,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_3 = CreateWindow(L"button", L"3", WS_CHILD | WS_VISIBLE,
      2 * width / 4 - 10 + 6, 50,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_c = CreateWindow(L"button", L"C", WS_CHILD | WS_VISIBLE,
      3 * width / 4 - 20 + 9, 50,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);

    button_4 = CreateWindow(L"button", L"4", WS_CHILD | WS_VISIBLE,
      10, 90,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_5 = CreateWindow(L"button", L"5", WS_CHILD | WS_VISIBLE,
      width / 4 + 3, 90,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_6 = CreateWindow(L"button", L"6", WS_CHILD | WS_VISIBLE,
      2 * width / 4 - 10 + 6, 90,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);

    button_7 = CreateWindow(L"button", L"7", WS_CHILD | WS_VISIBLE,
      10, 130,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_8 = CreateWindow(L"button", L"8", WS_CHILD | WS_VISIBLE,
      width / 4 + 3, 130,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_9 = CreateWindow(L"button", L"9", WS_CHILD | WS_VISIBLE,
      2 * width / 4 - 10 + 6, 130,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    button_0 = CreateWindow(L"button", L"0", WS_CHILD | WS_VISIBLE,
      3 * width / 4 - 20 + 9, 130,
      button_width, 30,
      hWnd, (HMENU)0, hInst, 0);
    break;
  }
  case WM_COMMAND:
    if (lParam == (LPARAM)button_1) setValue(output_area, L'1');
    if (lParam == (LPARAM)button_2) setValue(output_area, L'2');
    if (lParam == (LPARAM)button_3) setValue(output_area, L'3');
    if (lParam == (LPARAM)button_c) setValue(output_area, L'c');

    if (lParam == (LPARAM)button_4) setValue(output_area, L'4');
    if (lParam == (LPARAM)button_5) setValue(output_area, L'5');
    if (lParam == (LPARAM)button_6) setValue(output_area, L'6');

    if (lParam == (LPARAM)button_7) setValue(output_area, L'7');
    if (lParam == (LPARAM)button_8) setValue(output_area, L'8');
    if (lParam == (LPARAM)button_9) setValue(output_area, L'9');
    if (lParam == (LPARAM)button_0) setValue(output_area, L'0');
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

VOID setValue(HWND area, WCHAR ch) {
  if (ch == L'c')
    areaValue = L"0";
  else if (areaValue.length() > 30)
    return;
  else if (ch == L'0' && areaValue == L"0")
    return;
  else if (areaValue == L"0")
    areaValue = ch;
  else {
    areaValue.push_back(ch);
  }

  SetWindowText(area, areaValue.c_str());
}