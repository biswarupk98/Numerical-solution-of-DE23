import matplotlib.pyplot as plt
import numpy as np
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

X,Y = np.meshgrid(x,y)

plt.contourf(X,Y,tempDist, levels=30)
plt.xlabel('x position')
plt.ylabel('y position')
plt.colorbar()
plt.show()