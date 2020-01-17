class Laptop {
  private String
      mark,
      model;
  private float
      CPU_clockRate,
      GPU_clockRate;
  private int
      RAM_size,
      GPU_RAM_size;

  // Конструкор без параметров
  Laptop() {}

  // Коснструктор с параметрами
  Laptop(String mark, String model, float CPU_clockRate, float GPU_clockRate, int RAM_size, int GPU_RAM_size) {
    this.mark = mark;
    this.model = model;
    this.CPU_clockRate = CPU_clockRate;
    this.GPU_clockRate = GPU_clockRate;
    this.RAM_size = RAM_size;
    this.GPU_RAM_size = GPU_RAM_size;
  }

  // Деструктора в java нет, вместо него работает автоматический сборщик мусора
  
  public String GetMark() {
      return mark;
  }

  public String GetModel() {
    return model;
  }

  public float getCPUcr() {
    return CPU_clockRate;
  }

  public float GetGPUcr() {
    return GPU_clockRate;
  }

  public int GetRAMs() {
    return RAM_size;
  }

  public int GetGPUrs() {
    return GPU_RAM_size;
  }

  public String SetMark(String value) {
    mark = value;
    return value;
  }

  public String SetModel(String value) {
    model = value;
    return value;
  }

  public float SetCPUcr(float value) {
    CPU_clockRate = value;
    return value;
  }

  public float SetGPUcr(float value) {
    GPU_clockRate = value;
    return value;
  }

  public int SetRAMs(int value) {
    RAM_size = value;
    return value;
  }

  public int SetGPUrs(int value) {
    GPU_RAM_size = value;
    return value;
  }
}
