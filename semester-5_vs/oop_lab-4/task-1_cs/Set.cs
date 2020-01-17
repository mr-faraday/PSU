using System;
using System.Collections.Generic;
using System.Text;

namespace task_1_cs {
  class cell<T> where T : IComparable<T> {
    public cell<T> next = null;
    public T value;
  }

  class Set<T> where T : IComparable<T> {
    private const int maxSize = 1024;

    private cell<T> arrStart;
    private int mSize;
    private int size;

    private void insert(T value) {
      // Для пустого массива
      if (size == 0) {
        arrStart = new cell<T>();
        arrStart.value = value;

        size++;
        return;
      }

      cell<T> p;
      p = arrStart;

      while (p != null) {
        // Уже есть
        if (value.CompareTo(p.value) == 0) break;
        // Вставить в начало
        if (value.CompareTo(p.value) < 0 && p == arrStart) {
          arrStart = new cell<T>();
          arrStart.value = value;
          arrStart.next = p;

          size++;
          break;
        }
        // Вставить в конце
        if (value.CompareTo(p.value) > 0 && p.next == null) {
          p.next = new cell<T>;
          p.next.value = value;

          size++;
          break;
        }
        // Вставить в середине
        if (value.CompareTo(p.value) < 0) {
          cell<T> temp = p;
          p = new cell<T>();
          p.value = value;
          p.next = temp;

          size++;
          break;
        }

        p = p.next;
      }
    }

    private void clear() {
      this.size = 0;
      arrStart = null;
    }

    public Set() {
      size = 0;
      arrStart = null;
    }
    // Incomplete
    public void input() {
      T ob;
      Console.WriteLine("Введите значение(ия):");
      //ob = Console.ReadLine();

    }
    // Incomplete
    public void print() {
      if (size == 0) return;
      cell<T> p = arrStart;
      while (p != null) {
        Console.WriteLine("");
        p = p.next;
      }
      Console.WriteLine();
    }
    public int Int() {
      return size;
    }

    // Оператор присваивания в C# не перегружается
    public static Set<T> operator + (Set<T> set, T value) {
      set.insert(value);

      return set;
    }
    public static Set<T> operator * (Set<T> set_L, Set<T> set_R) {
      Set<T> cross = new Set<T>();

      cell<T> p1, p2;
      p1 = set_L.arrStart;
      for (uint i = 0; i < set_L.size; i++) {
        p2 = set_R.arrStart;
        for (uint j = 0; j < set_R.size; j++) {
          if (p1.value.CompareTo(p2.value) == 0) cross.insert(p1.value);
          p2 = p2.next;
        }
        p1 = p1.next;
      }

      return cross;
    }
  }
}
 