class Domain {
  static private Domain firstObj = null;
  private Domain nextObj = null;

  public Domain() {}
  public Domain(String domainName) {
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

  protected void getInfo() {
    System.out.println(domainName);
    System.out.println();
  }

  protected String domainName;
}