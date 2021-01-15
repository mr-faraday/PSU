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
 * Server.cs
 */

using Server;
using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;
using System.Threading;

namespace UdpServer {
  class Program {
    static int localPort = 3000;
    static Connections connections = new Connections();

    static void Main (string[] args) {
      try {

        Thread receiveThread = new Thread(new ThreadStart(ReceiveMessage));
        receiveThread.Start();
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      }
    }

    private static void ReceiveMessage () {
      UdpClient server = new UdpClient(localPort);
      IPEndPoint remoteIp = new IPEndPoint(IPAddress.Any, localPort);

      try {
        while (true) {
          byte[] bytes = server.Receive(ref remoteIp);

          // Announcement
          string announce = "Coonected IP: " + remoteIp.ToString();
          connections.announcement(announce, server);

          // connections.addConnection(remoteIp);
          // List<string> ips = connections.getConnectedClientsIp();
          // string data = string.Join(", ", ips);
          // byte[] response = Encoding.Unicode.GetBytes(data);
          // server.Send(response, response.Length, remoteIp);
        }
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      } finally {
        server.Close();
      }
    }
  }
}
