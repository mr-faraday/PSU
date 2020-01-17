class City extends Metropolis {
  public City(String cityName) {
    super("unknown");
    this.cityName = cityName;
  }
  protected void getInfo() {
    System.out.println(domainName);
    System.out.println(metropolisName);
    System.out.println(cityName);
    System.out.println();
  }
  protected String cityName;
}