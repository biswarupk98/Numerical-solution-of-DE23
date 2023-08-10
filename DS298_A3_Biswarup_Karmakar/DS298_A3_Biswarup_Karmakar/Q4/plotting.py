import numpy as np
import matplotlib.pyplot as plt
# Define the grid spacing and domain range
dx = 0.5
x_start = 0
x_end = 10
# Calculate the number of nodes on the grid
num = int((x_end - x_start) // dx) + 1
# Initialize the matrix A
A = np.zeros((num, num))
# Fill the matrix A with boundary condition
for i in range(num):
    if i == 0 or i == num-1:
        A[i, i] = 1
    else:
        A[i, i-1:i+2] = [-1/dx, 2/dx, -1/dx]
# Define the right-hand side vector b        
b = np.zeros(num)
b[1:-1] = -2.5e-9
# Solve the system of equations Au=b
u = np.linalg.solve(A, b)

x = np.linspace(x_start, x_end, num)
# Plot the solution
plt.figure()
plt.plot(x, u, marker='o')
plt.xlabel('x(distance measured along the bar’s length)')
plt.ylabel('u(deflection)')
plt.title('u vs x')
plt.show()
