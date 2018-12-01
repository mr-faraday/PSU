/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №2
 * Задание 1
 * В центре рабочей области окна расположено окно без заголовка с вертикальной и горизонтальной полосами прокрутки размером в четверть рабочей области. При нажатии разных клавиш мыши временное окно выдает различные сообщения.
 */

#include <windows.h>

 // Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
LPCWSTR szTitle = L"Лабараторная работа №2";    // Текст строки заголовка
LPCWSTR szWindowClass = L"Main";                // имя класса главного окна
LPCWSTR TempWindowClass = L"TempWindow";        // имя класса временного окна
HWND main_window;
HWND temp_window;

ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                RegisterTempWindow(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TempWndProc(HWND, UINT, WPARAM, LPARAM);

VOID                CreateTemp(PCWSTR msg);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
  MyRegisterClass(hInstance);
  RegisterTempWindow(hInstance);

  // Выполнить инициализацию приложения:
  if (!InitInstance(hInstance, nCmdShow)) {
    return FALSE;
  }

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
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = (LPCWSTR)NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  return RegisterClassExW(&wcex);
}

ATOM RegisterTempWindow(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = TempWndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = (LPCWSTR)NULL;
  wcex.lpszClassName = TempWindowClass;
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  HWND
    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }

  main_window = hWnd;
  ShowWindow(hWnd, SW_MAXIMIZE);
  UpdateWindow(hWnd);

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
    // Нажатие левой кнопки мыши
  case WM_LBUTTONDOWN:
    CreateTemp(L"Нажатие левой кнопки мыши");
    break;
    // Нажатие правой кнопки мыши
  case WM_RBUTTONDOWN:
    CreateTemp(L"Нажатие правой кнопки мыши");
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

LRESULT CALLBACK TempWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);
  switch (message) {
  case WM_CREATE:
    SetTimer(hWnd, 0, 1000, NULL);
    break;
  case WM_TIMER:
    DestroyWindow(hWnd);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

VOID CreateTemp(PCWSTR msg) {
  UINT width = 400;
  UINT height = 400;

  temp_window = CreateWindowW(TempWindowClass, nullptr, WS_CHILD | WS_BORDER | WS_HSCROLL | WS_VSCROLL,
    (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1),
    (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1),
    width, height, main_window, NULL, hInst, 0);

  HWND text = CreateWindow(L"static", NULL,
    WS_CHILD | WS_VISIBLE,
    10, 10, width - 40, height - 40, temp_window,
    (HMENU)0, hInst, 0);

  SetWindowText(text, msg);
  ShowWindow(text, SW_SHOW);

  if (!temp_window) {
    return;
  }

  ShowWindow(temp_window, SW_SHOW);
  UpdateWindow(temp_window);
}