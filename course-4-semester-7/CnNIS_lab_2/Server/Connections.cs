using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Server {
  class Connections {
    public List<IPEndPoint> clients = new List<IPEndPoint>();

    public bool addConnection(IPEndPoint ip) {
      bool foundClient = clients.Exists(c => c.ToString() == ip.ToString());
      if (foundClient) return false;

      clients.Add(ip);

      return true;
    }
  }
}
