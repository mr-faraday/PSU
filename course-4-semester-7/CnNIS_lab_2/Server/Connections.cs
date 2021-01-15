using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Server {
  class Connections {
    static ClientConnection[] clients;

    public void addConnection(IPEndPoint ip) {
      int id = this.getNextId();
      clients.Append(new ClientConnection(ip));
    }

    public void announcement(string data, UdpClient server) {
      foreach (ClientConnection client in clients) {
        byte[] sendData = Encoding.Unicode.GetBytes(data);
        server.Send(sendData, sendData.Length, client.ip);
      }
    }

    public List<string> getConnectedClientsIp() {
      var ips = new List<string>();
      foreach (ClientConnection client in clients) {
        ips.Add(client.RequestIp());
      }

      return ips;
    }

    private int getNextId() {
      return 0;
    }
  }
}
