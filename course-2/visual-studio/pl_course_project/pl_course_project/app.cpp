#define MAX_LOADSTRING 63

#include <iostream>  // Для отладки
#include <Windows.h>
#include "app.h"
#include "render.h"
#include "resource.h"
#include "globals.h"
#include "reversi.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

struct Cell {
  USHORT row;
  USHORT column;
};

WCHAR   szWindowClass[64];  // Имя класса окна приложения
WCHAR   szTitle[64];  // Заголовок окна
LPCWSTR check = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit posuere.";

ATOM                RegisterWinClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, INT);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void  App_Clear();
void  App_Init(bool mode);
int   App_move(Cell cell, HWND hWnd);
void  App_end(HWND hWnd, bool* is_saved);
bool  GetCell_byClick(Cell& cell, USHORT x, USHORT y);  // Определяет на какую клетку нажали [0..7, 0..7] 

int init(unsigned int hInst, int nCmdShow) {
  HINSTANCE hInstance = (HINSTANCE)hInst;

  // Инициализация глобальных строк
  LoadStringW(hInstance, IDS_WIN_CLASSNAME, szWindowClass, MAX_LOADSTRING);
  LoadStringW(hInstance, IDS_WINDOW_TITLE, szTitle, MAX_LOADSTRING);
  RegisterWinClass(hInstance);

  // Выполнить инициализацию приложения:
  if (!InitInstance(hInstance, nCmdShow)) return FALSE;

  MSG msg;
  BOOL bRet = 0;
  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));

  // Цикл основного сообщения:
  while (bRet = GetMessage(&msg, nullptr, 0, 0)) {
    if (-1 == bRet) break;
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      if (!IsDialogMessage(msg.hwnd, &msg)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }

  Render_shutDown();
  Render_killFont();

  return (int) msg.wParam;
}

ATOM RegisterWinClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = /*(HBRUSH)(COLOR_WINDOW + 1)*/(HBRUSH)GetStockObject(BLACK_BRUSH);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

  return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, INT nCmdShow) {
  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
    CW_USEDEFAULT, 0, wndWidth, wndHeight, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static bool is_saved = 1;
  static HINSTANCE hInst = GetModuleHandle(NULL);

  switch (message) {
  case WM_CREATE: {
    Render_glInit((unsigned int) hWnd);
    App_Clear();

    EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVE, MF_DISABLED | MF_GRAYED);

    Render_renderScene();
    break;
  }
  case WM_SIZE: {
    int nWidth = LOWORD(lParam);		// Ширина
    int nHeight = HIWORD(lParam);		// Высота

    Render_glResize(nWidth, nHeight);
    Render_renderScene();

    break;
  }
  case WM_MOVE: {
    Render_renderScene();

    break;
  }
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    // Разобрать выбор в меню:
    switch (wmId) {
    case IDM_NEWGAME_AI: {
      App_Clear();
      gameMode = 0;
      App_Init(gameMode);

      EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVE, MF_ENABLED);
      is_saved = FALSE;

      Render_renderScene();
      break;
    }
    case IDM_NEWGAME_2P: {
      App_Clear();
      gameMode = 1;
      App_Init(gameMode);

      EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVE, MF_ENABLED);
      is_saved = FALSE;

      Render_renderScene();
      break;
    }
    case IDM_OPEN: {
      OPENFILENAME ofn = {0};
      WCHAR szDirect[256];
      WCHAR szFileName[256];
      ofn.lStructSize = sizeof(ofn);
      ofn.hwndOwner = hWnd;
      ofn.lpstrFilter = L"Файл игры \"Реверси\"\0"
        L"*.reversi\0"
        L"Все файлы\0"
        L"*\0\0";
      ofn.lpstrFile = (LPWSTR) szDirect;
      *(ofn.lpstrFile) = 0;
      ofn.nMaxFile = sizeof(szDirect);
      ofn.nFilterIndex = 1;
      ofn.lpstrFileTitle = (LPWSTR) szFileName;
      *(ofn.lpstrFileTitle) = 0;
      ofn.nMaxFileTitle = sizeof(szFileName);
      ofn.lpstrInitialDir = nullptr;
      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
      if (!GetOpenFileName(&ofn)) break;

      HANDLE hFile;
      hFile = CreateFile(szDirect, GENERIC_READ, NULL, NULL, OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL, 0);

      // Проверка файла
      WCHAR buff[65];
      ReadFile(hFile, buff, sizeof(WCHAR)*64, nullptr, NULL);
      buff[64] = '\0';
      if (wcscmp(buff, check) != 0) {
        MessageBox(hWnd, L"Файл не соответствует типу."/*std::to_wstring(sizeof(check)).c_str()*/, L"Ошибка", MB_OK | MB_ICONHAND);

        CloseHandle(hFile);
        break;
      }

      App_Clear();

      ReadFile(hFile, (LPVOID) &gameMode, sizeof(gameMode), nullptr, NULL);
      ReadFile(hFile, (LPVOID) &whoMoves, sizeof(whoMoves), nullptr, NULL);
      ReadFile(hFile, (LPVOID) &board, sizeof(char)*64, nullptr, NULL);

      EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVE, MF_ENABLED);

      is_saved = TRUE;
      CloseHandle(hFile);

      switch (gameMode) {
        // Игра с ИИ
      case 0:
        wcscpy_s(firstString_buff, 32, L"Вы");
        wcscpy_s(secondString_buff, 32, L"Компьютер");

        break;

        // Игра на 2 игрока
      case 1:
        wcscpy_s(firstString_buff, 32, L"Игрок 1");
        wcscpy_s(secondString_buff, 32, L"Игрок 2");

        break;
      }

      Reversi_setScore();

      Render_renderScene();
      break;
    }
    case IDM_SAVE: {
      OPENFILENAME ofn = {0};
      WCHAR szDirect[512] = L"game.reversi";
      WCHAR szFileName[512];
      ofn.lStructSize = sizeof(ofn);
      ofn.hwndOwner = hWnd;
      ofn.lpstrFilter = L"Файл игры \"Реверси\"\0"
        L"*.reversi\0"
        L"Все файлы\0"
        L"*\0\0";
      ofn.lpstrFile = szDirect;
      ofn.nMaxFile = sizeof(szDirect);
      ofn.nFilterIndex = 1;
      ofn.lpstrFileTitle = szFileName;
      *(ofn.lpstrFileTitle) = 0;
      ofn.nMaxFileTitle = sizeof(szFileName);
      ofn.lpstrInitialDir = nullptr;
      ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
      if (!GetSaveFileName(&ofn)) break;

      HANDLE hFile;
      hFile = CreateFile(szDirect, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL, 0);

      WriteFile(hFile, check, sizeof(WCHAR)*64, nullptr, NULL);
      WriteFile(hFile, (LPVOID) &gameMode, sizeof(gameMode), nullptr, NULL);
      WriteFile(hFile, (LPVOID) &whoMoves, sizeof(whoMoves), nullptr, NULL);
      /*for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)*/
      WriteFile(hFile, (LPVOID) &board, sizeof(char)*64, nullptr, NULL);

      CloseHandle(hFile);
      is_saved = TRUE;

      break;
    }
    case IDM_ABOUT: {
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);

      break;
    }
    case IDM_EXIT: {
      if (!is_saved) {
        switch (MessageBox(hWnd, L"Сохранить игру?", L"Выход", MB_YESNOCANCEL | MB_ICONEXCLAMATION)) {
        case IDYES: {
          SendMessage(hWnd, WM_COMMAND, IDM_SAVE, NULL);

          break;
        }
        case IDNO: {
          DestroyWindow(hWnd);

          break;
        }
        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
        }
      }
      else DestroyWindow(hWnd);

      break;
    }
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }

    break;
  }
  case WM_CLOSE: {
    SendMessage(hWnd, WM_COMMAND, IDM_EXIT, NULL);
    
    break;
  }
  case WM_LBUTTONDOWN: {
    USHORT
      cX = LOWORD(lParam),
      cY = fieldHeight - HIWORD(lParam);

    Cell cell;
    if (!GetCell_byClick(cell, cX, cY)) break;
    if (!whoMoves) break;

    if (App_move(cell, hWnd) == END_GAME) App_end(hWnd, &is_saved);

    Render_renderScene();
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

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);

  switch (message) {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;
  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}

void App_Clear() {
  for (size_t i = 0; i < 8; i++)
    for (size_t j = 0; j < 8; j++) board[i][j] = 0;

  blackScore = 0;
  whiteScore = 0;
  whoMoves = 0;

  firstString_buff[0] = '\0',
  secondString_buff[0] = '\0';
}

void App_Init(bool mode) {
  switch (mode) {
  // Игра с ИИ
  case 0:
    wcscpy_s(firstString_buff, 32, L"Вы");
    wcscpy_s(secondString_buff, 32, L"Компьютер");

    blackScore = 2;
    whiteScore = 2;

    whoMoves = BLACK_can_move;

    board[3][3] = BLACK_s;
    board[3][4] = WHITE_s;
    board[4][3] = WHITE_s;
    board[4][4] = BLACK_s;

    break;

  // Игра на 2 игрока
  case 1:
    wcscpy_s(firstString_buff, 32, L"Игрок 1");
    wcscpy_s(secondString_buff, 32, L"Игрок 2");

    blackScore = 2;
    whiteScore = 2;

    whoMoves = BLACK_can_move;

    board[3][3] = BLACK_s;
    board[3][4] = WHITE_s;
    board[4][3] = WHITE_s;
    board[4][4] = BLACK_s;

    break;
  }

  Reversi_setPosibleMoves();
}

int App_move(Cell cell, HWND hWnd) {
  // Неверный ход
  if (board[cell.row][cell.column] != whoMoves) {
    std::wcout << L"Неверный ход" << std::endl;
    return 0;
  }

  int state;
  if (state = Reversi_move(cell.row, cell.column)) {
    std::wcout << L"Error: " << state << std::endl;
    return 0;
  }
  PlaySound(MAKEINTRESOURCE(IDR_WAVE1),
            NULL,
            SND_RESOURCE | SND_ASYNC);

  // Очистка от возможных ходов
  Reversi_posibleMovesClear();

  // Смена хода
  if (whoMoves == BLACK_can_move) whoMoves = WHITE_can_move;
  else whoMoves = BLACK_can_move;

  // Подсчёт фишек
  Reversi_setScore();
  Render_renderScene();

  // Выставление возможных ходов другой стороны 
  // Если нет возможных ходов
  if (!Reversi_setPosibleMoves()) {
    // Смена сторон
    if (whoMoves == BLACK_can_move) whoMoves = WHITE_can_move;
    else whoMoves = BLACK_can_move;

    // Конец игры, если другая сторона тоже не имеет ходов
    if (!Reversi_setPosibleMoves()) return END_GAME;

    if (whoMoves == WHITE_can_move) MessageBox(hWnd, L"У чёрных нет ходов. Идут белые.", L"Кончились ходы", MB_OK);
    else MessageBox(hWnd, L"У белых нет ходов. Идут чёрные.", L"Кончились ходы", MB_OK);
  }

  // Ход ИИ
  if (!gameMode && whoMoves == WHITE_can_move) {
    Render_renderScene();
    Reversi_aiMove();
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1),
              NULL,
              SND_RESOURCE | SND_ASYNC);

    // Очистка от возможных ходов
    Reversi_posibleMovesClear();

    // Смена сторон
    if (whoMoves == BLACK_can_move) whoMoves = WHITE_can_move;
    else whoMoves = BLACK_can_move;

    Reversi_setScore();
    Render_renderScene();

    if (!Reversi_setPosibleMoves()) {
      // Смена сторон
      if (whoMoves == BLACK_can_move) whoMoves = WHITE_can_move;
      else whoMoves = BLACK_can_move;

      // Конец игры, если другая сторона тоже не имеет ходов
      if (!Reversi_setPosibleMoves()) return END_GAME;

      if (whoMoves == WHITE_can_move) MessageBox(hWnd, L"У чёрных нет ходов. Идут белые.", L"Кончились ходы", MB_OK);
      else MessageBox(hWnd, L"У белых нет ходов. Идут чёрные.", L"Кончились ходы", MB_OK);
    }
  }
  
  return 0;
}

void App_end(HWND hWnd, bool* is_saved) {
  if (blackScore > whiteScore) MessageBox(hWnd, L"Победили чёрные.", L"Конец игры", MB_OK);
  else if (blackScore < whiteScore) MessageBox(hWnd, L"Победили белые.", L"Конец игры", MB_OK);
  else MessageBox(hWnd, L"Ничья.", L"Конец игры", MB_OK);

  *is_saved = TRUE;
}

bool GetCell_byClick(Cell& cell ,USHORT x, USHORT y) {

  // Выход за рамки доски
  if (y - yInit < 0 ||
      y - yInit > boardSize ||
      x - xInit < 0 ||
      x - xInit > boardSize)
    return FALSE;

  cell.row = (y - yInit) / (boardSize/8);
  cell.column = (x - xInit) / (boardSize / 8);

  return TRUE;
}
