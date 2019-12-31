class Place extends City {
  public Place(String placeName) {
    super("unknown");
    this.placeName = placeName;
  }
  protected void getInfo() {
    System.out.println(domainName);
    System.out.println(metropolisName);
    System.out.println(cityName);
    System.out.println(placeName);
    System.out.println();
  }
  protected String placeName;
}