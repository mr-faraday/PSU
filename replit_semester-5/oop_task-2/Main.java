class Main extends Domain {
  public static void main(String[] args) {
    Domain dom1 = new Domain("Columbia");
    Domain dom2 = new Domain("Alaska");
    Domain dom3 = new Domain("Washington");
    Domain dom4 = new Domain("Wisconsin");
    Domain dom5 = new Domain("Georgia");
    Metropolis metro1 = new Metropolis("Highway");
    Metropolis metro2 = new Metropolis("Brooklin");
    City city1 = new City("New York");
    Place bridge1 = new Place("Golden Gate");

    Domain.showList();
  }
}