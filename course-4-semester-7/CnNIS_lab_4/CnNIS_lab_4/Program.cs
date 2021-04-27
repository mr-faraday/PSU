using System;
using System.Security.Cryptography;
using System.IO;

namespace CnNIS_lab_4 {
  class Program {
    private static readonly SHA256 encryptor = SHA256.Create();

    static void Main (string[] args) {
      Console.Write("File name: ");
      string filePath = Console.ReadLine();

      FileStream stream = File.OpenRead(filePath);
      byte[] outputBuffer = encryptor.ComputeHash(stream);

      Console.WriteLine("\nChecksum:");
      for (int i = 0; i < outputBuffer.Length; i++) {
        Console.Write($"{outputBuffer[i]:X2}");
        if (i + 1 != outputBuffer.Length) Console.Write(":");
      }


      Console.WriteLine();
    }
  }
}
