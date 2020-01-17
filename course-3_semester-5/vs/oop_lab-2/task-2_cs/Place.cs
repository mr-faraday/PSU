using System;
using System.Collections.Generic;
using System.Text;

namespace task_2_cs {
  class Place : City {
    public Place(string placeName) : base("unknown") {
      this.placeName = placeName;
    }
    protected override void getInfo() {
      Console.WriteLine(domainName);
      Console.WriteLine(metropolisName);
      Console.WriteLine(cityName);
      Console.WriteLine(placeName);
      Console.WriteLine();
    }
    protected string placeName;
  }
}
