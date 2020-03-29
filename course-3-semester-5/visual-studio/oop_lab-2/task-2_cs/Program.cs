/* Ляхович Д.А.
 * 17-ИТд
 * Вариант 8
 *
 * Объектно-ориентированные технологии программирования и стандарты проектирования
 * Лабораторная №2
 * Задание 1
 * Порядок выполнения работы.
 *  1. Определить иерархию классов (место, область, город, мегаполис).
 *  2. Определить в классе статическую компоненту - указатель на начало связанного списка объектов и статическую функцию для просмотра списка.
 *  3. Реализовать классы.
 *  4. Написать демонстрационную программу, в которой создаются объекты различных классов и помещаются в список, после чего список просматривается.
 *  5. Сделать соответствующие методы не виртуальными и посмотреть,
что будет.
 *  6. Реализовать аналог на языке С# и Java.
 */

using System;

namespace task_2_cs {
  class Program {
    static void Main(string[] args) {
      Domain dom1 = new Domain("Columbia");
      Domain dom2 = new Domain("Alaska");
      Domain dom3 = new Domain("Washington");
      Domain dom4 = new Domain("Wisconsin");
      Domain dom5 = new Domain("Georgia");
      Metropolis metro1 = new Metropolis("Highway");
      Metropolis metro2 = new Metropolis("Brooklin");
      City city1 = new City("New York");
      Place bridge1 = new Place("Golden Gate");

      Domain.showList();
    }
  }
}
