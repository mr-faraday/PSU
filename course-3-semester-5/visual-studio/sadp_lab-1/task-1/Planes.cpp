#include "Planes.h"

int Planes::input(const std::wstring& rec) {
  // Проверка ввода;
  const wchar_t* p = rec.c_str();  // Указатель для чтения ввода
  int n, x;

  UINT num = 0;
  wchar_t mark[20] = { L'\0' };
  UINT year = 0;
  UINT time = 0;

  // Чтение серийного номера
  if (swscanf_s(p, L"%u", &num) != 1) return 0;  // Чтение
  n = 1;
  x = num;
  while ((x /= 10) > 0) n++;  // Колличество цифр
  p = p + n;  // Смещение указателя
  if (*p != L' ' || n != 8) return 0;  // Проверка на пробел и восьмизнаность
  p++;

  // Считывать строку до запятой
  for (UINT i = 0; i < 20; i++) {
    if ((*p == L',' || *p == L' ') && i == 0) return 0;
    if (*p == L',') break;
    mark[i] = *p;
    p++;
  }
  p++;
  if (*p != L' ') return 0;
  p++;

  // Считывание года выпуска
  if (swscanf_s(p, L"%u", &year) != 1) return 0;  // Чтение
  n = 1;
  x = year;
  while ((x /= 10) > 0) n++;  // Колличество цифр
  p = p + n;  // Смещение указателя
  if (*p != L',' || n != 4) return 0;  // Проверка на запятую и четырехзначность
  p++;
  if (*p != L' ') return 0;
  p++;

  // Считывание времени налета
  if (swscanf_s(p, L"%u", &time) != 1) return 0;  // Чтение
  n = 1;
  x = time;
  while ((x /= 10) > 0) n++;  // Колличество цифр
  p = p + n;  // Смещение указателя
  if (*p != L'\0') return 0;  // Проверка на конец строки
  
  Plane* r = new Plane;
  r->serialNum = num;
  r->mark_model = mark;
  r->year = year;
  r->flyTime = time;

  insert(r);

  return 1;
}

void Planes::insert(Plane* rec) {
  // Если первый
  if (size == 0) {
    listStart = rec;

    size++;
    return;
  }

  Plane* p = listStart;
  while (p != nullptr) {
    // Если последний
    if (rec->serialNum > p->serialNum && p->next == nullptr) {
      p->next = rec;
      rec->prev = p;

      size++;
      return;
    }

    // Перед первым
    if (p == listStart && rec->serialNum <= p->serialNum) {
      listStart = rec;
      rec->next = p;
      p->prev = rec;

      size++;
      return;
    }

    // Перед текущим не первым
    if (rec->serialNum <= p->serialNum) {
      p->prev->next = rec;
      rec->prev = p->prev;
      rec->next = p;
      p->prev = rec;

      size++;
      return;
    }

    p = p->next;
  }
}

Plane* Planes::deleteRec(Plane* rec) {
  // Единственный элемент
  if (size == 1) {
    delete rec;
    listStart = nullptr;

    size--;
    return nullptr;
  }

  // Первый элемент
  if (rec->prev == nullptr) {
    listStart = rec->next;
    rec->next->prev = nullptr;
    delete rec;

    size--;
    return listStart;
  }

  // Последний элемент
  if (rec->next == nullptr) {
    rec->prev->next = nullptr;
    delete rec;

    size--;
    return nullptr;
  }

  // Элемент в середине;
  Plane* retPl;
  rec->prev->next = rec->next;
  rec->next->prev = rec->prev;
  retPl = rec->next;
  delete rec;

  size--;
  return retPl;
}

Planes::Planes() {
  std::wstring rec;

  std::wcout << L"Введите записи в формате:\n\r";
  std::wcout << L"[Серийный номер(целое восьмизначное число)] [Марка – модель(строка, максимум 20 символов)], [Год выпуска(целое четырёхзначное число)], [Время начета(целое число в часах)]\n\r";
  std::wcout << L"Для завершения нажмите Enter с пустой строкой\n\r";
  std::wcout << L"\n\r";

  std::getline(std::wcin, rec);
  while (!rec.empty()) {
    if (!input(rec)) std::wcout << L"Не коректный ввод\n\r";
    std::wcout << L"\n\r";
    rec.clear();
    std::getline(std::wcin, rec);
  }
}

Planes::~Planes() {
  Plane* p = listStart;
  while (p != nullptr) {
    listStart = p->next;
    delete p;
    p = listStart;
  }
}

void Planes::planesFilter(UINT cupTime) {
  Plane* p = listStart;
  while (p != nullptr)
    if (p->flyTime >= cupTime)
      p = deleteRec(p);
    else p = p->next;
}

void Planes::printList() {
  if (size == 0) return;

  Plane* p = listStart;
  while (p != nullptr) {
    std::wcout << L"Серийный номер:   " << p->serialNum << L"\n\r";
    std::wcout << L"Марка-модель:     " << p->mark_model << L"\n\r";
    std::wcout << L"Год выпуска:      " << p->year << L"\n\r";
    std::wcout << L"Часов налёта:     " << p->flyTime << L"\n\r";
    std::wcout << L"\n\r";
    
    p = p->next;
  }
}
