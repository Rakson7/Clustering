import matplotlib.pyplot as plt
import numpy as np
import sys
import subprocess


minpts = sys.argv[1]
epsilon = sys.argv[2]
filename = sys.argv[3]
subprocess.call(["./optics.out", minpts, epsilon, filename])

in_file = open("./optics.txt")
data = [[float(n) for n in line.split()] for line in in_file]
points = np.array(data)
x = np.arange(len(data))
y = points[:, [1]]

plt.bar(x, y)
plt.show()
