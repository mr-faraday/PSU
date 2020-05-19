/*
 * Ляхович Д.А.
 * 17-ИТд
 * 9 вариант
 * ОСиСП
 * Лабороторная работа №5
 * 
 * Задание 9
 * Реализовать функционал шифрования и дешифровки строки.
 * Шифрования производится по следующему алгоритму: производится перестановка
 * первого символа со вторым, третий с четвертым и т. д.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;

namespace Interface {
  static class Program {
    /// <summary>
    /// Главная точка входа для приложения.
    /// </summary>
    [STAThread]
    [DllImport(
      "F:\\PSU\\course-3-semester-6\\ossp\\lab-5\\Debug\\LIB_StringEncrypt.dll",
      CharSet = CharSet.Unicode
    )]
    public static extern string encrypt (StringBuilder newStr, int size, string str);

    [DllImport(
      "F:\\PSU\\course-3-semester-6\\ossp\\lab-5\\Debug\\LIB_StringEncrypt.dll",
      CharSet = CharSet.Unicode
    )]
    public static extern string decrypt (StringBuilder newStr, int size, string str);

    static void Main () {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      Application.Run(new MainWindow());
    }
  }
}
