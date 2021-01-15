/**
 * Ляхович Д.А.
 * 17-ИТд
 * Вариант 9
 * 
 * Защита информационных ресурсов компьютерных систем и сетей
 * Лабораторная работа №2
 * 
 * Организовать взаимодействие типа клиент - сервер. Сервер при подключении
 * к нему нового клиента высылает список IP-адресов уже подключенных
 * клиентов. А остальным клиентам рассылается сообщение в виде IP-адреса о
 * том, что подключился такой-то клиент. Протокол UDP.
 * 
 * Client.cs
 */

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace UdpServer {
  class Program {
    static string remoteAddress = "127.0.0.1";
    static int remotePort = 3000;

    static void Main (string[] args) {
      try {
        SendMessage(); // отправляем сообщение
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      }
    }
    private static void SendMessage () {
      UdpClient client = new UdpClient(); // создаем UdpClient для отправки сообщений
      IPEndPoint remoteIp = new IPEndPoint(IPAddress.Any, remotePort);

      try {
        byte[] connect = Encoding.Unicode.GetBytes("Connecting");

        Console.Write("Press any key to connect ... ");
        Console.ReadKey();
        Console.WriteLine();
        client.Send(connect, connect.Length, remoteAddress, remotePort); // отправка

        while (true) {
          byte[] data = client.Receive(ref remoteIp);
          string message = Encoding.Unicode.GetString(data);
          Console.WriteLine(message);
        }
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      } finally {
        client.Close();
      }
    }
  }
}
