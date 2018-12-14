/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 *
 * Языки программирования
 * Лабораторная №5
 * Задание 1
 * В рамках данной лабораторной работы необходимо, используя Win32API, разработать программу, в главном окне которого отображается список записей определенного типа. В главном меню окна содержится два пункта: «Файл» и «Сортировка». В пункте «Файл» содержатся пункты: «Открыть», «Сохранить» и «Выход». «Сортировать» содержатся пункты для выполнения сортировки списка, набор пунктов задается в индивидуальном варианте задания. При вызове контекстного меню на списке отображается меню, содержащее пункты «Добавить», «Изменить», «Удалить».
 * НАКЛАДНАЯ:
 * - Номер накладной (целое число);
 * - Дата накладной (в формате дд.мм.гггг);
 * - Общая сумма по накладной (вещественное число);
 * - ФИО оператора (строка 20 символов).
 * Формат ввода: Номер, «Дата», Сумма, ФИО оператора.
 * По номеру накладной в порядке убывания, по номеру накладной в порядке возрастания, по ФИО ответственного лица в порядке возрастания, по ФИО ответственного лица в порядке убывания.
 */

//#define CONSOLE_OUTPUT       _setmode(_fileno(stdout), _O_U16TEXT);
//#pragma comment             (linker, "/SUBSYSTEM:CONSOLE")
//#pragma comment             (linker, "/ENTRY:wWinMainCRTStartup")
//#include <conio.h>
//#include <iostream>
//#include <io.h>
//#include <fcntl.h>

#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <algorithm>
#include "resource.h"

#pragma comment(lib,"Comctl32.lib")  // Подключение ListView Controller

#define MAX_LOADSTRING                    100

struct Record {
  INT invoiceNum;
  SYSTEMTIME date;
  FLOAT amount;
  WCHAR fullName[21];
};

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
std::vector<Record> db;
LPCWSTR header[] = { L"Номер накладной", L"Дата накладной", L"Общая сумма", L"ФИО оператора" };
INT CONST colNum = 4;
INT CONST textMaxLen = 20;
WCHAR check[512] = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce pretium convallis lacus vitae ultricies. Nulla eget nunc et ex placerat ullamcorper. Vivamus vulputate massa sit amet velit auctor feugiat at in erat. Aliquam varius velit venenatis bibendum suscipit. Nulla pellentesque tellus eget ornare consequat. Curabitur non sagittis libero. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed risus sapien, euismod a sapien sed, efficitur varius nisi massa nunc.";
BOOLEAN is_saved = TRUE;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, INT);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Create(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Edit(HWND, UINT, WPARAM, LPARAM);

HWND                CreateListView(HWND, UINT);
BOOL    WINAPI      AddListViewItems(HWND, INT, INT, SIZE_T);
INT                 SetListViewColumns(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  #ifdef CONSOLE_OUTPUT
  CONSOLE_OUTPUT
  #endif

  // Initialize Common Controls
  INITCOMMONCONTROLSEX InitCtrlEx;
  InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
  InitCtrlEx.dwICC = ICC_LISTVIEW_CLASSES;
  if (!InitCommonControlsEx(&InitCtrlEx)) {
    int nResult = GetLastError();
    MessageBox(NULL,
               L"Could not initialize common controls!\r\n",
               L"Initialization failure",
               MB_ICONERROR);
  }

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
  wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TASK1);
  wcex.lpszClassName  = szWindowClass;
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, INT nCmdShow) {
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static HWND hWnd_LV;
  
  switch (message) {
  case WM_CREATE: {
    if (!(hWnd_LV = CreateListView(hWnd, NULL)))
      MessageBox(hWnd, L"Невозможно создать элемент ListView", L"Ошибка", MB_OK);
    SetListViewColumns(hWnd_LV);
    ShowWindow(hWnd_LV, SW_SHOWDEFAULT);

    EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVE, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT1, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT2, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT3, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT4, MF_DISABLED | MF_GRAYED);
  }
  break;
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    // Разобрать выбор в меню:
    switch (wmId) {
    case IDM_OPEN: {
      if (db.size() > 0)
        if (MessageBox(hWnd,
          L"Данные будут потеряны, продолжить?",
          L"Открытие файла",
          MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2)
          == IDNO)
          break;

      OPENFILENAME ofn = { 0 };
      WCHAR szDirect[256];
      WCHAR szFileName[256];
      ofn.lStructSize = sizeof(ofn);
      ofn.hwndOwner = hWnd;
      ofn.lpstrFilter = L"Файл лабараторной работы №5\0"
                        L"*.LAB5\0"
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
      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
      if (!GetOpenFileName(&ofn)) break;

      HANDLE hFile;
      hFile = CreateFile(szDirect, GENERIC_READ, NULL, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, 0);

      // Проверка файла
      WCHAR buff[512];
      ReadFile(hFile, (LPVOID)buff, sizeof(buff), nullptr, NULL);
      if (wcscmp(buff, check) != 0) {
        MessageBox(hWnd, L"Файл не соответствует типу.", L"Ошибка", MB_OK | MB_ICONHAND);

        CloseHandle(hFile);
        break;
      }

      // Очистка вектора и таблицы
      if (db.size() > 0)
        while (db.size() > 0) db.erase(db.begin());
      ListView_DeleteAllItems(hWnd_LV);

      // Колличество записей
      SIZE_T size = 0;
      ReadFile(hFile, (LPVOID)&size, sizeof(size), nullptr, NULL);

      // Считывание записей
      Record tmp;
      for (SIZE_T i = 0; i < size; i++) {
        ReadFile(hFile, (LPVOID)&tmp, sizeof(Record), nullptr, NULL);
        db.push_back(tmp);
        AddListViewItems(hWnd_LV, colNum, textMaxLen, db.size() - 1);
      }

      is_saved = TRUE;
      CloseHandle(hFile);
      break;
    }
    case IDM_SAVE: {
      OPENFILENAME ofn = { 0 };
      WCHAR szDirect[512] = L"table.lab5";
      WCHAR szFileName[512];
      ofn.lStructSize = sizeof(ofn);
      ofn.hwndOwner = hWnd;
      ofn.lpstrFilter = L"Файл лабараторной работы №5\0"
                        L"*.LAB5\0"
                        L"Все файлы\0"
                        L"*\0\0";
      ofn.lpstrFile = szDirect;
      ofn.nMaxFile = sizeof(szDirect);
      ofn.nFilterIndex = 1;
      ofn.lpstrFileTitle = szFileName;
      *(ofn.lpstrFileTitle) = 0;
      ofn.nMaxFileTitle = sizeof(szFileName);
      ofn.lpstrInitialDir = nullptr;
      ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;
      if (!GetOpenFileName(&ofn)) break;

      HANDLE hFile;
      hFile = CreateFile(szDirect, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, 0);

      
      WriteFile(hFile, (LPVOID)check, sizeof(check), nullptr, NULL);

      SIZE_T size = db.size();
      WriteFile(hFile, (LPVOID)&size, sizeof(size), nullptr, NULL);
      for (SIZE_T i = 0; i < db.size(); i++) {
        WriteFile(hFile, (LPVOID)&db[i], sizeof(Record), nullptr, NULL);
      }

      CloseHandle(hFile);
      is_saved = TRUE;
      break;
    }
    case IDM_ABOUT: {
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    }
    case IDM_CREATE: {
      if (DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATE), hWnd, Create))
        AddListViewItems(hWnd_LV, colNum, textMaxLen, db.size() - 1);
      if (db.size() == 1) {
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVE, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT1, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT2, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT3, MF_ENABLED);
        EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_SORT4, MF_ENABLED);
        is_saved = FALSE;
      }

      break;
    }
    case IDM_EDIT: {
      INT iPos = ListView_GetNextItem(hWnd_LV, -1, LVNI_SELECTED);
      std::wstring str;

      if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_CREATE), hWnd, Edit, iPos)) {
        LVITEMW lvi;
        lvi.mask = LVIF_TEXT;
        lvi.cchTextMax = textMaxLen;
        lvi.iItem = iPos;

        str = std::to_wstring(db[iPos].invoiceNum);
        lvi.pszText = &str[0];
        lvi.iSubItem = 0;

        if (!ListView_SetItem(hWnd_LV, &lvi))
          return FALSE;
        str = std::to_wstring(db[iPos].date.wDay);
        str += L"." + std::to_wstring(db[iPos].date.wMonth);
        str += L"." + std::to_wstring(db[iPos].date.wYear);
        ListView_SetItemText(hWnd_LV, iPos, 1, (LPWSTR)str.c_str());
        str.erase(0, std::wstring::npos);
        str = std::to_wstring(db[iPos].amount);
        ListView_SetItemText(hWnd_LV, iPos, 2, (LPWSTR)str.c_str());
        ListView_SetItemText(hWnd_LV, iPos, 3, (LPWSTR)db[iPos].fullName);
      }
      
      is_saved = FALSE;
      break;
    }
    case IDM_DELETE: {
      if (MessageBox(hWnd,
                     (L"Удалить выделенные(" + std::to_wstring(ListView_GetSelectedCount(hWnd_LV)) + L") объекты?").c_str(),
                     L"Удаление записей",
                     MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2)
        == IDYES) {
        INT iPos = ListView_GetNextItem(hWnd_LV, -1, LVNI_SELECTED);
        INT c = 0;
        INT it_m;
        std::vector<Record>::iterator it = db.begin();

        while (iPos != -1) {
          it_m = iPos - c;
          it = db.erase(it + it_m);
          c++;
          iPos = ListView_GetNextItem(hWnd_LV, iPos, LVNI_SELECTED);
        }

        iPos = ListView_GetNextItem(hWnd_LV, -1, LVNI_SELECTED);

        while (iPos != -1) {
          ListView_DeleteItem(hWnd_LV, iPos);
          iPos = ListView_GetNextItem(hWnd_LV, -1, LVNI_SELECTED);
        }

        is_saved = FALSE;
      }

      break;
    }
    case IDM_SORT1: {
      std::sort(db.begin(), db.end(), [](const Record& a, const Record& b) {
        return a.invoiceNum > b.invoiceNum;
      });
      
      // Синхронизация
      std::wstring str;
      for (SIZE_T i = 0; i < db.size(); i++) {
        LVITEMW lvi;
        lvi.mask = LVIF_TEXT;
        lvi.cchTextMax = textMaxLen;
        lvi.iItem = i;

        str = std::to_wstring(db[i].invoiceNum);
        lvi.pszText = &str[0];
        lvi.iSubItem = 0;

        if (!ListView_SetItem(hWnd_LV, &lvi))
          return FALSE;
        str = std::to_wstring(db[i].date.wDay);
        str += L"." + std::to_wstring(db[i].date.wMonth);
        str += L"." + std::to_wstring(db[i].date.wYear);
        ListView_SetItemText(hWnd_LV, i, 1, (LPWSTR)str.c_str());
        str.erase(0, std::wstring::npos);
        str = std::to_wstring(db[i].amount);
        ListView_SetItemText(hWnd_LV, i, 2, (LPWSTR)str.c_str());
        ListView_SetItemText(hWnd_LV, i, 3, (LPWSTR)db[i].fullName);
      }

      is_saved = FALSE;
      break;
    }
    case IDM_SORT2: {
      std::sort(db.begin(), db.end(), [](const Record& a, const Record& b) {
        return a.invoiceNum < b.invoiceNum;
      });

      // Синхронизация
      std::wstring str;
      for (SIZE_T i = 0; i < db.size(); i++) {
        LVITEMW lvi;
        lvi.mask = LVIF_TEXT;
        lvi.cchTextMax = textMaxLen;
        lvi.iItem = i;

        str = std::to_wstring(db[i].invoiceNum);
        lvi.pszText = &str[0];
        lvi.iSubItem = 0;

        if (!ListView_SetItem(hWnd_LV, &lvi))
          return FALSE;
        str = std::to_wstring(db[i].date.wDay);
        str += L"." + std::to_wstring(db[i].date.wMonth);
        str += L"." + std::to_wstring(db[i].date.wYear);
        ListView_SetItemText(hWnd_LV, i, 1, (LPWSTR)str.c_str());
        str.erase(0, std::wstring::npos);
        str = std::to_wstring(db[i].amount);
        ListView_SetItemText(hWnd_LV, i, 2, (LPWSTR)str.c_str());
        ListView_SetItemText(hWnd_LV, i, 3, (LPWSTR)db[i].fullName);
      }


      is_saved = FALSE;
      break;
    }
    case IDM_SORT3: {
      std::sort(db.begin(), db.end(), [](const Record& a, const Record& b) {
        return a.fullName < b.fullName;
      });

      // Синхронизация
      std::wstring str;
      for (SIZE_T i = 0; i < db.size(); i++) {
        LVITEMW lvi;
        lvi.mask = LVIF_TEXT;
        lvi.cchTextMax = textMaxLen;
        lvi.iItem = i;

        str = std::to_wstring(db[i].invoiceNum);
        lvi.pszText = &str[0];
        lvi.iSubItem = 0;

        if (!ListView_SetItem(hWnd_LV, &lvi))
          return FALSE;
        str = std::to_wstring(db[i].date.wDay);
        str += L"." + std::to_wstring(db[i].date.wMonth);
        str += L"." + std::to_wstring(db[i].date.wYear);
        ListView_SetItemText(hWnd_LV, i, 1, (LPWSTR)str.c_str());
        str.erase(0, std::wstring::npos);
        str = std::to_wstring(db[i].amount);
        ListView_SetItemText(hWnd_LV, i, 2, (LPWSTR)str.c_str());
        ListView_SetItemText(hWnd_LV, i, 3, (LPWSTR)db[i].fullName);
      }

      is_saved = FALSE;
      break;
    }
    case IDM_SORT4: {
      std::sort(db.begin(), db.end(), [](const Record& a, const Record& b) {
        return a.fullName > b.fullName;
      });

      // Синхронизация
      std::wstring str;
      for (SIZE_T i = 0; i < db.size(); i++) {
        LVITEMW lvi;
        lvi.mask = LVIF_TEXT;
        lvi.cchTextMax = textMaxLen;
        lvi.iItem = i;

        str = std::to_wstring(db[i].invoiceNum);
        lvi.pszText = &str[0];
        lvi.iSubItem = 0;

        if (!ListView_SetItem(hWnd_LV, &lvi))
          return FALSE;
        str = std::to_wstring(db[i].date.wDay);
        str += L"." + std::to_wstring(db[i].date.wMonth);
        str += L"." + std::to_wstring(db[i].date.wYear);
        ListView_SetItemText(hWnd_LV, i, 1, (LPWSTR)str.c_str());
        str.erase(0, std::wstring::npos);
        str = std::to_wstring(db[i].amount);
        ListView_SetItemText(hWnd_LV, i, 2, (LPWSTR)str.c_str());
        ListView_SetItemText(hWnd_LV, i, 3, (LPWSTR)db[i].fullName);
      }

      is_saved = FALSE;
      break;
    }
    case IDM_EXIT: {
      if (!is_saved) {
        switch (MessageBox(hWnd, L"Изменения не сохранены. Сохранить?", L"Выход", MB_YESNOCANCEL | MB_ICONEXCLAMATION)) {
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
      } else DestroyWindow(hWnd);

      break;
    }
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }

    break;
  }
  case WM_NOTIFY: {
    switch (((LPNMHDR)lParam)->code) {
    case NM_RCLICK: {
      INT iPos = ListView_GetNextItem(hWnd_LV, -1, LVNI_SELECTED);

      hWnd_LV;
      HMENU hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDC_CONTEXT));

      if (iPos == -1) {
        EnableMenuItem(GetSubMenu(hMenu, 0), IDM_EDIT, MF_DISABLED | MF_GRAYED);
        EnableMenuItem(GetSubMenu(hMenu, 0), IDM_DELETE, MF_DISABLED | MF_GRAYED);
      }
      hMenu = GetSubMenu(hMenu, 0);

      POINT m;
      GetCursorPos(&m);

      TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,
        m.x,
        m.y, 0, hWnd, NULL);
      DestroyMenu(hMenu);
    }
    break;
    case LVN_DELETEALLITEMS: {

    }
    break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }

    break;
  }
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
    EndPaint(hWnd, &ps);

    break;
  }
  case WM_SIZE: {
    RECT rcl;
    GetClientRect(hWnd, &rcl);

    SetWindowPos(hWnd_LV, 0, 0, 0, rcl.right, rcl.bottom, SWP_NOZORDER);
    ListView_SetColumnWidth(hWnd_LV, 3, -2);

    for (INT i = 0; i < 4; i++)
    ListView_SetColumnWidth(hWnd_LV, i, (rcl.right - rcl.left) / colNum);
    
    break;
  }
  case WM_CLOSE: {
    SendMessage(hWnd, WM_COMMAND, IDM_EXIT, NULL);

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

INT_PTR CALLBACK Create(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);

  switch (message) {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg, IDC_AMOUNT, L"0.00");
    return (INT_PTR)TRUE;
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    switch (wmId) {
    case IDYES: {
      Record tmp;
      WCHAR buff[64];

      GetDlgItemText(hDlg, IDC_NUM, buff, 64);
      buff[63] = '\0';
      try {
        tmp.invoiceNum = std::stoi(buff);
      } catch (const std::exception&) {
        MessageBox(NULL, L"Неверно введен номер.", L"Ошибка", MB_OK);
        return (INT_PTR)TRUE;
      }
      for (WCHAR *ch = buff; *ch != '\0'; ch++) *ch = '\0';

      DateTime_GetSystemtime(GetDlgItem(hDlg, IDC_DATE), &tmp.date);

      GetDlgItemText(hDlg, IDC_AMOUNT, buff, 64);
      buff[63] = '\0';
      std::wstring subStr = L".0123456789";
      CHAR dots = 0;
      for (WCHAR *ch = buff; *ch != '\0'; ch++) {
        if (*ch == '.') dots++;
        if (subStr.find(*ch) == -1 || dots > 1) {
          MessageBox(NULL, L"Неверно введена сумма.", L"Ошибка", MB_OK);
          return (INT_PTR)TRUE;
        }
      }      
      tmp.amount = std::wcstof(buff, NULL);

      GetDlgItemText(hDlg, IDC_FULLNAME, tmp.fullName, 21);
      if (tmp.fullName[0] == L'\0') {
        MessageBox(NULL, L"Введите Ф.И.О.", L"Ошибка", MB_OK);
        return (INT_PTR)TRUE;
      }
      
      db.push_back(tmp);

      EndDialog(hDlg, 1);
      return (INT_PTR)TRUE;
    }
    break;
    case IDCANCEL:
      EndDialog(hDlg, 0);
      return (INT_PTR)FALSE;
      break;
    default:
      return (INT_PTR)FALSE;
    }
  }
  default:
    return (INT_PTR)FALSE;
  }
  return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Edit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  static INT iPos;

  switch (message) {
  case WM_INITDIALOG: {
    std::wstring buff;
    iPos = lParam;
    buff = std::to_wstring(db[iPos].invoiceNum);
    SetDlgItemText(hDlg, IDC_NUM, (LPWSTR) buff.c_str());
    DateTime_SetSystemtime(
      GetDlgItem(hDlg, IDC_DATE),
      GDT_VALID,
      &db[iPos].date
    );
    buff.erase(0, std::wstring::npos);
    buff = std::to_wstring(db[iPos].amount);
    SetDlgItemText(hDlg, IDC_AMOUNT, (LPWSTR)buff.c_str());
    SetDlgItemText(hDlg, IDC_FULLNAME, db[iPos].fullName);

    SetWindowText(GetDlgItem(hDlg, IDYES), L"Изменить");
    SetWindowText(hDlg, L"Изменить запись");
  }
  return (INT_PTR)TRUE;
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    switch (wmId) {
    case IDYES: {
      Record tmp;
      WCHAR buff[64];

      GetDlgItemText(hDlg, IDC_NUM, buff, 64);
      buff[63] = '\0';
      try {
        tmp.invoiceNum = std::stoi(buff);
      }
      catch (const std::exception&) {
        MessageBox(NULL, L"Неверно введен номер.", L"Ошибка", MB_OK);
        return (INT_PTR)TRUE;
      }
      for (WCHAR *ch = buff; *ch != '\0'; ch++) *ch = '\0';

      DateTime_GetSystemtime(GetDlgItem(hDlg, IDC_DATE), &tmp.date);

      GetDlgItemText(hDlg, IDC_AMOUNT, buff, 64);
      buff[63] = '\0';
      std::wstring subStr = L".0123456789";
      CHAR dots = 0;
      for (WCHAR *ch = buff; *ch != '\0'; ch++) {
        if (*ch == '.') dots++;
        if (subStr.find(*ch) == -1 || dots > 1) {
          MessageBox(NULL, L"Неверно введена сумма.", L"Ошибка", MB_OK);
          return (INT_PTR)TRUE;
        }
      }
      tmp.amount = std::wcstof(buff, NULL);

      GetDlgItemText(hDlg, IDC_FULLNAME, tmp.fullName, 21);
      if (tmp.fullName[0] == L'\0') {
        MessageBox(NULL, L"Введите Ф.И.О.", L"Ошибка", MB_OK);
        return (INT_PTR)TRUE;
      }

      db[iPos] = tmp;

      EndDialog(hDlg, 1);
    }
    return (INT_PTR)TRUE;
    case IDCANCEL:
      EndDialog(hDlg, 0);
      return (INT_PTR)FALSE;
    default:
      return (INT_PTR)FALSE;
    }
  }
  default:
    return (INT_PTR)FALSE;
  }
  return (INT_PTR)FALSE;
}

BOOL WINAPI AddListViewItems(HWND hWnd_LV, INT colNum, INT textMaxLen, SIZE_T index) {
  INT iLastIndex = ListView_GetItemCount(hWnd_LV);
  std::wstring str;
  
  LVITEMW lvi;
  lvi.mask = LVIF_TEXT;
  lvi.cchTextMax = textMaxLen;
  lvi.iItem = iLastIndex;

  str = std::to_wstring(db[index].invoiceNum);
  lvi.pszText = &str[0];
  lvi.iSubItem = 0;

  if (ListView_InsertItem(hWnd_LV, &lvi) == -1)
    return FALSE;
  str = std::to_wstring(db[index].date.wDay);
  str += L"." + std::to_wstring(db[index].date.wMonth);
  str += L"." + std::to_wstring(db[index].date.wYear);
  ListView_SetItemText(hWnd_LV, iLastIndex, 1, (LPWSTR) str.c_str());
  str.erase(0, std::wstring::npos);
  str = std::to_wstring(db[index].amount);
  ListView_SetItemText(hWnd_LV, iLastIndex, 2, (LPWSTR)str.c_str());
  ListView_SetItemText(hWnd_LV, iLastIndex, 3, (LPWSTR)db[index].fullName);

  return TRUE;
}

INT SetListViewColumns(HWND hWnd_LV) {
  RECT rcl;
  GetClientRect(hWnd_LV, &rcl);

  INT index = -1;

  LVCOLUMN lvc;
  lvc.mask = LVCF_TEXT | LVCF_WIDTH;
  lvc.cx = (rcl.right - rcl.left) / colNum;
  lvc.cchTextMax = textMaxLen;

  for (INT i = 0; i < colNum; i++) {
    lvc.pszText = (LPWSTR)header[i];
    index = ListView_InsertColumn(hWnd_LV, i, &lvc);
    if (index == -1) break;
  }

  return index;
}

HWND CreateListView(HWND hWndParent, UINT uId) {
  RECT rcl;
  GetClientRect(hWndParent, &rcl);

  HWND hWnd_LV = CreateWindowW(WC_LISTVIEW, L"",
    WS_CHILD | LVS_REPORT,
    0, 0, rcl.right - rcl.left, rcl.bottom - rcl.top - 50,
    hWndParent, nullptr, hInst, NULL);
  SendMessage(hWnd_LV, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
  ListView_SetExtendedListViewStyleEx(hWnd_LV, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

  return (hWnd_LV);
}
