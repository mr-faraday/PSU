using System;
using System.Collections.Generic;
using System.Text;

namespace task_1_cs {
  class Char {
    public char value = '\0';
    public Char next;
  }

  class Chars {
    private Char listStart;
    private uint maxSize = 2048;
    private uint size;

    public Chars() {
      size = 0;
    }
    ~Chars() {}

    public void print() {
      Console.WriteLine(listStart.value);
    }

    public void input() {
      Console.WriteLine("Введите символ: ");
      char ch = (char)Console.Read();
      this.insert(ch);
    }

    public char getCh() {
      if (listStart == null) return '0';
      return listStart.value;
    }

    private void insert(char ch) {
      if (size == maxSize) return;
      Char ch_temp = listStart;
      listStart = new Char();
      listStart.value = ch;
      listStart.next = ch_temp;

      size++;
    }

    public static Chars operator + (Chars chs, char ch) {
      chs.insert(ch);
      return chs;
    }

    public static Chars operator -- (Chars chs) {
      if (chs.size == 0) return chs;
      if (chs.size == 1) {
        chs.listStart = null;
        chs.size--;
        return chs;
      }
      chs.listStart = chs.listStart.next;
      chs.size--;
      return chs;
    }
    public static bool operator == (char ch, Chars chs) {
      return ch == chs.listStart.value;
    }
    public static bool operator != (char ch, Chars chs) {
      return ch != chs.listStart.value;
    }
  }
}
