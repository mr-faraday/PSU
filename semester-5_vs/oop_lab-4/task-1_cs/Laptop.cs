using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task_1_cs {
  public interface IComparable<T> {
    int CompareTo(T obj);
  }

  class Laptop : IComparable<Laptop> {
    int IComparable<Laptop>.CompareTo(Laptop obj) {
      // 1 поле
      if (this.mark.CompareTo(obj.mark) > 0) return 1;
      else if (this.mark.CompareTo(obj.mark) < 0) return -1;
      // 2 поле
      else if (this.model.CompareTo(obj.model) > 0) return 1;
      else if (this.model.CompareTo(obj.model) < 0) return -1;
      // 3 поле
      else if (this.CPU_clockRate > obj.CPU_clockRate) return 1;
      else if (this.CPU_clockRate < obj.CPU_clockRate) return -1;
      // 4 поле
      else if (this.GPU_clockRate > obj.GPU_clockRate) return 1;
      else if (this.GPU_clockRate < obj.GPU_clockRate) return -1;
      // 5 поле
      else if (this.RAM_size > obj.RAM_size) return 1;
      else if (this.RAM_size < obj.RAM_size) return -1;
      // 6 поле
      else if (this.GPU_RAM_size > obj.GPU_RAM_size) return 1;
      else if (this.GPU_RAM_size < obj.GPU_RAM_size) return -1;

      return 0;
    }
      // Свойтва объектов
    private string
      mark,
      model;
    private float
      CPU_clockRate,
      GPU_clockRate;
    private int
      RAM_size,
      GPU_RAM_size;

      // Конструктор с параметрами
    public Laptop(
      string mark,
      string model,
      float CPU_clockRate,
      float GPU_clockRate,
      int RAM_size,
      int GPU_RAM_size
    ) {
      this.mark = mark;
      this.model = model;
      this.CPU_clockRate = CPU_clockRate;
      this.GPU_clockRate = GPU_clockRate;
      this.RAM_size = RAM_size;
      this.GPU_RAM_size = GPU_RAM_size;
    }

      // Конструктор без параметров
    public Laptop() {
      this.mark = "Empty";
      this.model = "Empty";
      this.CPU_clockRate = 0;
      this.GPU_clockRate = 0;
      this.RAM_size = 0;
      this.GPU_RAM_size = 0;
    }

    ~Laptop() {}

    public string GetMark() {
      return mark;
    }

    public string GetModel() {
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

    public string SetMark(string value) {
      mark = value;
      return value;
    }

    public string SetModel(string value) {
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
}
