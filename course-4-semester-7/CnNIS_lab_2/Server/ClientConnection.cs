using System;
using System.Collections.Generic;
using System.Net;
using System.Text;

namespace Server {
  class ClientConnection {
    public IPEndPoint ip;

    public ClientConnection(IPEndPoint ip) {
      this.ip = ip;
    }

    public string RequestIp() {
      return this.ip.ToString();
    }
  }
}
