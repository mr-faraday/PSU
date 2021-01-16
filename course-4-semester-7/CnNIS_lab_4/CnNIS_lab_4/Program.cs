using System;
using System.Security.Cryptography;
using System.Text;

namespace CnNIS_lab_4 {
  class Program {
    static void Main (string[] args) {
      string input = Console.ReadLine();

      SHA256 coder = SHA256.Create();

      byte[] inputBuffer = Encoding.Unicode.GetBytes(input);
      byte[] outputBuffer = coder.ComputeHash(inputBuffer);

      for (int i = 0; i < outputBuffer.Length; i++) {
        Console.Write($"{outputBuffer[i]:X2}");
        if ((i % 4) == 3) Console.Write(" ");
      }

    }
  }
}
