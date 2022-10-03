import os
from matplotlib import pyplot as plt

def form_result(folder, type):
   directory = 'results_' + folder + "/" + type

   with open("results_" + folder + "/" + type + "/total.txt", "w") as w:
      for filename in os.listdir(directory):
         file = os.path.join(directory, filename)
         if os.path.isfile(file):
            with open(file) as r:
                  lines = r.readlines()
                  for line in lines:
                     w.write(line)

def read_values(file):
   result = []
   with open(file, "r") as f:
      for line in f.readlines():
         result.append(float(line))
   return result

def plot_results(folder):
   dgemm = read_values(folder + "/dgemm/total.txt")
   simple = read_values(folder + "/simple/total.txt")
   
   count = min(len(dgemm), len(simple))
   
   plt.xscale("symlog", base=2)
   plt.yscale("symlog", base=2)
   
   plt.xlabel("Количество потоков")
   plt.ylabel("Ускорение вычислений")
   
   plt.grid(True)
   
   xs = [2**x for x in range(0, count)]
   ys = [simple[i] / dgemm[i] for i in range(0, count)]
   
   plt.title("Слабая масштабируемость")
   plt.plot(xs, ys, "-o")
   plt.show()
                           
#form_result("strong", "dgemm")

plot_results("results_weak")