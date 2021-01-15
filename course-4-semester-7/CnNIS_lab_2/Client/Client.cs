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
using System.Threading;

namespace UdpServer {
  class Program {
    static string remoteAddress = "127.0.0.1";
    static int remotePort = 3000;
    static int localPort = 3000;

    static void Main (string[] args) {
      try {
        //Console.Write("Введите порт для прослушивания: "); // локальный порт
        //localPort = Int32.Parse(Console.ReadLine());
        //Console.Write("Введите удаленный адрес для подключения: ");
        //remoteAddress = Console.ReadLine(); // адрес, к которому мы подключаемся
        //Console.Write("Введите порт для подключения: ");
        //remotePort = Int32.Parse(Console.ReadLine()); // порт, к которому мы подключаемся

        // Thread receiveThread = new Thread(new ThreadStart(ReceiveMessage));
        // receiveThread.Start();
        SendMessage(); // отправляем сообщение
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      }
    }
    private static void SendMessage () {
      UdpClient client = new UdpClient(); // создаем UdpClient для отправки сообщений
      IPEndPoint remoteIp = new IPEndPoint(IPAddress.Any, localPort);

      try {
        byte[] connect = Encoding.Unicode.GetBytes("Connecting");
        client.Send(connect, connect.Length, remoteAddress, remotePort); // отправка

        while (true) {
          byte[] data = client.Receive(ref remoteIp);

          string message = Encoding.Unicode.GetString(data);
          Console.WriteLine("Response: ", message);

          // string message = Console.ReadLine(); // сообщение для отправки
          // byte[] data = Encoding.Unicode.GetBytes(message);
          // client.Send(data, data.Length, remoteAddress, remotePort); // отправка
        }
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      } finally {
        client.Close();
      }
    }

    private static void ReceiveMessage () {
      UdpClient receiver = new UdpClient(localPort); // UdpClient для получения данных
      IPEndPoint remoteIp = null; // адрес входящего подключения

      try {
        while (true) {
          byte[] data = receiver.Receive(ref remoteIp); // получаем данные
          string message = Encoding.Unicode.GetString(data);
          Console.WriteLine("Собеседник: {0}", message);
        }
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      } finally {
        receiver.Close();
      }
    }
  }
}
