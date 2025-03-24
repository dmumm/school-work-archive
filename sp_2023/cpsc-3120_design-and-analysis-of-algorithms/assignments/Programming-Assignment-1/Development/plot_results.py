import matplotlib.pyplot as plt
import numpy as np

times = np.loadtxt('results.txt')
plt.plot(times)
plt.show()
