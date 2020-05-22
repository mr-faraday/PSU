/*
 * Ляхович Д.А.
 * 17-ИТд
 * 9 вариант
 * ОСиСП
 * Лабороторная работа №3
 * 
 * Задание 9
 * Поиск файлов по содержимому в различных каталогах, 
 * количество потоков в два раза меньше каталогов.
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace task_1 {
  class Program {

    static string searchPattern = "792";
    static string sDir = @"D:\F";
    static int threads;

    static void Main (string[] args) {

      search(sDir);

      while (threads != 0) {
        Thread.Sleep(1000);
      }
    }

    async static void search (string path) {

      string firstDirectory = "";
      bool isSecondDirectory = false;

      foreach (string f in Directory.EnumerateFiles(path, "*", SearchOption.TopDirectoryOnly)) {
        foreach (string line in File.ReadLines(f)) {
          if (line.IndexOf(searchPattern) != -1) {
            Console.WriteLine(f);
            break;
          }
        }
      }

      try {

        foreach (string d in Directory.EnumerateDirectories(path, "*", SearchOption.TopDirectoryOnly)) {
          if (isSecondDirectory && firstDirectory.Length != 0) {

            threads++;
            await Task.Run(() => search(firstDirectory, d));

            firstDirectory = "";
            isSecondDirectory = false;

          } else if (isSecondDirectory) {

            threads++;
            await Task.Run(() => search(d));

            isSecondDirectory = false;
            firstDirectory = "";

          } else {

            firstDirectory = d;
            isSecondDirectory = true;

          }
        }

      } catch(UnauthorizedAccessException ex) {
        Console.WriteLine(ex.Message);
      }

    }

    static void search (string path1, string path2) {

      search(path1);
      search(path2);

      threads--;

    }
  }
}
