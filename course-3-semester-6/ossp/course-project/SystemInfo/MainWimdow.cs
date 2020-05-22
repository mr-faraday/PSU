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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic.Devices;
using System.Management;
using System.Diagnostics;

namespace SystemInfo {
  public partial class MainWimdow : Form {
    public MainWimdow () {
      InitializeComponent();

      Timer timer = new Timer();
      timer.Tick += new EventHandler(update);
      timer.Interval = 1000;
      timer.Start();

      machineName.Text = Environment.MachineName;
      userName.Text = Environment.UserName;
      biosDate.Text = DateTime.Now.ToString();
      ramSize.Text = new ComputerInfo().TotalPhysicalMemory.ToString();
      vramSize.Text = new ComputerInfo().TotalVirtualMemory.ToString();

      ManagementObjectSearcher cpu = new ManagementObjectSearcher("select * from Win32_Processor");
      foreach (ManagementObject obj in cpu.Get()) {
        cpuType.Text = obj["Name"].ToString();
        cpuFrequency.Text = obj["CurrentClockSpeed"].ToString() + " МГц";
      }

      screenResolution.Text = SystemInformation.VirtualScreen.Width.ToString() + "x" + SystemInformation.VirtualScreen.Height.ToString();

      ManagementObjectSearcher gpuAdapters = new ManagementObjectSearcher("select * from Win32_VideoController");
      foreach (ManagementObject obj in gpuAdapters.Get()) {
        GPUs.Items.Add(new GPU_Adapter(obj));
      }

      GPUs.SetSelected(0, true);

      processesUpdate();
    }

    private void update (Object myObject, EventArgs myEventArgs) {
      biosDate.Text = DateTime.Now.ToString();
    }

    private void GPUs_SelectedIndexChanged (object sender, EventArgs e) {
      GPU_Adapter item = GPUs.SelectedItem as GPU_Adapter;

      GPUs_name.Text = item.name;
      GPUs_deviceId.Text = item.deviceId;
      GPUs_proccessor.Text = item.videoProcessor;
      GPUs_architecture.Text = item.videoArchitecture;
      GPUs_vramSize.Text = item.adapterRAM;
      GPUs_vramType.Text = item.videoMemoryType;
      GPUs_driverVersion.Text = item.driverVersion;
    }

    private void processesRefresh_Click (object sender, EventArgs e) {
      processesUpdate();
    }

    private void processesUpdate () {
      List<ListViewItem> items = new List<ListViewItem>();
      foreach (Process process in Process.GetProcesses()) {
        ListViewItem item = new ListViewItem(new string[] {
          process.Id.ToString(),
          process.ProcessName,
          process.MainWindowTitle,
          String.Format("{0:0,0.00}", (double) process.WorkingSet64 / 1000000),
          process.BasePriority.ToString()
        });

        items.Add(item);
      }

      Processes.Items.Clear();
      Processes.Items.AddRange(items.ToArray());
    }
  }
}
