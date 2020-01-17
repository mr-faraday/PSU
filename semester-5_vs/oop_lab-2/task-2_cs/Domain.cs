using System;
using System.Collections.Generic;
using System.Text;

namespace task_2_cs {
  class Domain {
    static private Domain firstObj = null;
    private Domain nextObj = null;

    public Domain(string domainName) {
      this.domainName = domainName;
      if (firstObj == null) {
        firstObj = this;
        return;
      }
      
      Domain p = firstObj;
      while (p.nextObj != null) p = p.nextObj;
      p.nextObj = this;
    }
    static public void showList() {
      Domain p = firstObj;
      while (p != null) {
        p.getInfo();
        p = p.nextObj;
      }
    }

    protected virtual void getInfo() {
      Console.WriteLine(domainName);
      Console.WriteLine();
    }

    protected string domainName;
  }
}
