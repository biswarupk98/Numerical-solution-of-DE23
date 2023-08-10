import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

temp_csv = pd.read_csv('implicit_euler_x_y.txt', sep = '\t')

plt.figure()
plt.plot(temp_csv.iloc[:, 0], temp_csv.iloc[:, 1], c = 'red')
plt.xlabel('x')
plt.ylabel('y')
plt.title('y vs x plot for impicit euler')
plt.show()
plt.clf()