class Metropolis extends Domain {
  public Metropolis(String metropolisName) {
    super("unknown");
    this.metropolisName = metropolisName;
  }
  protected void getInfo() {
    System.out.println(domainName);
    System.out.println(metropolisName);
    System.out.println();
  }
  protected String metropolisName;
}