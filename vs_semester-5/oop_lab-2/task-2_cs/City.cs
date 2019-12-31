using System;
using System.Collections.Generic;
using System.Text;

namespace task_2_cs {
  class City : Metropolis {
    public City(string cityName) : base("unknown") {
      this.cityName = cityName;
    }
    protected override void getInfo() {
      Console.WriteLine(domainName);
      Console.WriteLine(metropolisName);
      Console.WriteLine(cityName);
      Console.WriteLine();
    }
    protected string cityName;
  }
}
