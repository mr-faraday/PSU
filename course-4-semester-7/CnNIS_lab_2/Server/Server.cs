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

using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
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
      IPEndPoint clientIp = new IPEndPoint(IPAddress.Any, localPort);

      try {
        while (true) {
          byte[] bytes = server.Receive(ref clientIp);

          // Send new connection information about all 
          List<IPEndPoint> ips = connections.clients;
          if (ips.Count > 0) {
            string newConnectMessage = "Coonected IP: " + string.Join(", ", ips);
            byte[] newConnectData = Encoding.Unicode.GetBytes(newConnectMessage);
            server.Send(newConnectData, newConnectData.Length, clientIp);
          } else {
            string newConnectMessage = "Server is empty";
            byte[] newConnectData = Encoding.Unicode.GetBytes(newConnectMessage);
            server.Send(newConnectData, newConnectData.Length, clientIp);
          }
          
          // Send to new connection all connects
          string announce = "New IP joined: " + clientIp.ToString();
          byte[] sendData = Encoding.Unicode.GetBytes(announce);
          connections.clients.ForEach(c => {
            server.Send(sendData, sendData.Length, c);
          });

          connections.addConnection(clientIp);
        }
      } catch (Exception ex) {
        Console.WriteLine(ex.Message);
      } finally {
        server.Close();
      }
    }
  }

  class Connections {
    public List<IPEndPoint> clients = new List<IPEndPoint>();

    public bool addConnection (IPEndPoint ip) {
      bool foundClient = clients.Exists(c => c.ToString() == ip.ToString());
      if (foundClient) return false;

      clients.Add(ip);

      return true;
    }
  }
}
