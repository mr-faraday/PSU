/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №4
 * Задание 1
 * При нажатии левой кнопки мыши в месте нажатия появляется красный кружок, который начинает плавно «падать» к нижней границе окна. Когда он ее достигает, то исчезает. Допускается присутствие нескольких кружков на экране одновременно.
 */

//#pragma comment (linker, "/SUBSYSTEM:CONSOLE")
//#pragma comment (linker, "/ENTRY:wWinMainCRTStartup")
//#include <iostream>

#include <windows.h>
#include <vector>

#define CIRCLE_VELOCITY            2
#define CIRCLE_VELOCITY_INCREASE   1.01
#define CIRCLE_RADIUS              50

struct circle {
  SHORT x;
  SHORT y;
  DOUBLE velocity;
  SHORT radius;
};

 // Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
LPCWSTR szTitle = L"Лабораторная работа №4";    // Текст строки заголовка
LPCWSTR szWindowClass = L"Main";                // имя класса главного окна
UINT width = 500;
UINT height = 500;
std::vector<circle> circles;                    // Массив кругов
SHORT h;

HWND hMain;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = (LPCWSTR)NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1),
    (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1),
    width, height, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }

  ShowWindow(hWnd, SW_SHOWMAXIMIZED);
  UpdateWindow(hWnd);

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_CREATE:
    hMain = hWnd;
    SetTimer(hWnd, 0, 1, NULL);
    break;
  case WM_SIZE:
    h = HIWORD(lParam);
    break;
  case WM_PAINT:
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hWnd, &ps);
    HBRUSH hBrush;
    HPEN hPen;
    hBrush = CreateSolidBrush(RGB(255, 0, 0));
    hPen = CreatePen(PS_NULL, 2, RGB(255, 0, 0));
    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);

    for (size_t i = 0; i < circles.size(); i++) {
      Ellipse(
        hdc,
        circles[i].x - circles[i].radius / 2,
        circles[i].y - circles[i].radius / 2,
        circles[i].x + circles[i].radius / 2,
        circles[i].y + circles[i].radius / 2
      );

      circles[i].y += circles[i].velocity;
      circles[i].velocity *= CIRCLE_VELOCITY_INCREASE;
    }

    EndPaint(hWnd, &ps);
    break;
  case WM_LBUTTONDOWN:
    circles.push_back({
      (SHORT)LOWORD(lParam),
      (SHORT)HIWORD(lParam),
      CIRCLE_VELOCITY,
      CIRCLE_RADIUS
    });
    break;
  case WM_TIMER:
    for (size_t i = 0; i < circles.size(); i++) {
      if (circles[i].y - 50 > h) circles.erase(circles.begin() + i);
    }
    InvalidateRect(hWnd, NULL, TRUE);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
