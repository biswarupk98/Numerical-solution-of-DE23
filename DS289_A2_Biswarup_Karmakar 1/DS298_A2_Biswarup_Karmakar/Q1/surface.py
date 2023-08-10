import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# read data from file
file = open("temperature_values.txt")
temp = file.readlines()

t1 = list(map(float,temp[0].split()))
dx, lx, ux = t1
Nx = round((ux-lx)/dx)+1
x = [ lx+i*dx for i in range(Nx) ]

t1 = list(map(float,temp[1].split()))
dy, ly, uy = t1
Ny = round((uy-ly)/dy)+1
y = [ ly+i*dy for i in range(Ny-1,-1,-1) ]

tempDist = np.zeros((Ny,Nx))

for i in range(2,len(temp)):
    tempDist[(i-2), :] = list(map(float,temp[i].split()))

# create mesh grid
X,Y = np.meshgrid(x,y)

# create 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X,Y,tempDist)

# set axis labels
ax.set_xlabel('x position')
ax.set_ylabel('y position')
ax.set_zlabel('temperature')

# show plot
plt.show()

#Contour plot
plt.contourf(X,Y,tempDist, levels=30)
plt.xlabel('x position')
plt.ylabel('y position')
plt.colorbar()
plt.show()