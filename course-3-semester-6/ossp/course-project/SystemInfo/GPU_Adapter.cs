/*
 * Copyright 2020 Lyakhovich Dmitry
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
