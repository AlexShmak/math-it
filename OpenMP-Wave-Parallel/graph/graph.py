import numpy as np
import matplotlib.pyplot as plt

solution = np.loadtxt("array.txt")

x = np.linspace(0, 1, solution.shape[0])
y = np.linspace(0, 1, solution.shape[1])
X, Y = np.meshgrid(x, y)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y, solution)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
