import os
import numpy as np
import matplotlib.pyplot as plt

ex1_dir = os.path.join("./GeantExample2Part1")
ex2_dir = os.path.join("./GeantExample2Part2")

def read_file(file):
    with open(file) as f:
        data = f.readlines()
        data = [line for line in data if not line[0].startswith('#')]
        data = [line.split('\n')[0] for line in data]
        data = np.array(data, dtype=float)

    return data

print(os.path.join(ex1_dir, "output_nt_Energy.csv"))

E1 = read_file(os.path.join(ex1_dir, "output_nt_Energy.csv"))

plt.hist(E1, bins=100, histtype='step')