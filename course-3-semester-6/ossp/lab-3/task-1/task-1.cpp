/*
 * Ляхович Д.А.
 * 17-ИТд
 * ОСиСП
 * Лабороторная работа №3
 * 9 вариант
 *
 * Задание 9
 * Поиск файлов по содержимому в различных каталогах, количество потоков в
 * два раза меньше каталогов.
 */

#define OUT std::wcout
#define IN  std::wcin

#include <conio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <thread>
#include <filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

bool hasActiveThread = false;
std::wstring fileFragment;
const fs::directory_options options = (
  fs::directory_options::follow_directory_symlink |
  fs::directory_options::skip_permission_denied
  );

void find(fs::directory_entry);
bool hasAccess(fs::directory_entry);

int main() {
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);

  OUT << L"Hello!\n" << L"Enter a file fragment: ";
  IN >> fileFragment;

  std::wstring path = L"F:\\";

  std::vector<std::thread> threads;
  std::list<fs::directory_entry> directories;
  for (const auto& entry : fs::directory_iterator(path, fs::directory_options(options))) {
    if (fs::is_directory(entry)) {
      // create thread
      hasActiveThread = true;
      std::thread (find, entry).detach();
    } else {
      // file scan
      //OUT << entry.path() << std::endl;
    }
  }

  while (true) {
    if (!hasActiveThread) break;

    //std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::wcout << L"scaned" << std::endl;
  /*std::thread t1(task1, L"Hello");
  t1.join();*/

  /*OUT << std::endl << L"Нажмите любую клавишу ... ";
  _getwch();*/
  return 0;
}

void find(fs::directory_entry directory) {
  hasActiveThread = true;

  // enter the folder
  for (const auto& entry : fs::directory_iterator(directory.path(), fs::directory_options(options))) {
    if (fs::is_directory(entry)) {
      // create thread
      hasActiveThread = true;
      std::thread (find, entry).detach();
    } else {
      // file scan
      OUT << entry.path() << std::endl;
    }
  }

  //hasActiveThread = false;
}
