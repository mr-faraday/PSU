using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Management;

namespace SystemInfo {
  class GPU_Adapter {
    public string name;
    public string deviceId;
    public string videoProcessor;
    public string videoArchitecture;
    public string adapterRAM;
    public string videoMemoryType;
    public string driverVersion;

    public GPU_Adapter (ManagementObject gpu) {
      name = gpu["Name"].ToString();
      deviceId = gpu["DeviceID"].ToString();
      videoProcessor = gpu["VideoProcessor"].ToString();
      videoArchitecture = gpu["VideoArchitecture"].ToString();
      adapterRAM = gpu["AdapterRAM"].ToString();
      videoMemoryType = gpu["VideoMemoryType"].ToString();
      driverVersion = gpu["DriverVersion"].ToString();
    }

    public string Name {
      get => name;
    }
  }
}
