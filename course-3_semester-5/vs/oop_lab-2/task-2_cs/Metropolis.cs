using System;
using System.Collections.Generic;
using System.Text;

namespace task_2_cs {
  class Metropolis : Domain {
    public Metropolis(string metropolisName) : base("unknown") {
      this.metropolisName = metropolisName;
    }
    protected override void getInfo() {
      Console.WriteLine(domainName);
      Console.WriteLine(metropolisName);
      Console.WriteLine();
    }
    protected string metropolisName;
  }
}
