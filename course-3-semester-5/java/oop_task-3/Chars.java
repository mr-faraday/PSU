import java.util.Scanner;

class Char {
  public char value;
  public Char next;
}

class Chars {
  private static Scanner sc = new Scanner(System.in);
  private Char listStart;
  private int maxSize = 2048;
  private int size;

  public Chars() {
    size = 0;
  }

  public void print() {
    System.out.println(listStart.value);
  }

  public void input() {
    System.out.println("Введите символ: ");
    char ch = sc.next().charAt(0);
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

  /*public static Chars operator + (Chars chs, char ch) {
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
  }*/
}