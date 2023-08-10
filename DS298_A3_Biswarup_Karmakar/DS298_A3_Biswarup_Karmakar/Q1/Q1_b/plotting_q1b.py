import numpy as np
import matplotlib.pyplot as plt

# Values of j
j_values = ["0.004000","0.014400","0.028800","0.047600","0.075000"]

# Loop over j values
for t in j_values:
    # Read data from output file
    filename = "q1_b_1024_" + str(t) + ".txt"
    data = np.loadtxt(filename)
    x = np.linspace(0, 1, len(data))
    u = data

    # Plot u vs x
    plt.plot(x, u, label="t = " + str(t))

# Add axis labels and legend
plt.xlabel("x")
plt.ylabel("u")
plt.title("u vs x for N=1024 with alpha=0.001")
plt.legend()

# Show plot
plt.show()


# comparison between 1(a) and 1(b) results
with open('../Q1_a/q1_a_1024_0.047600.txt','r') as file1:
    data1=np.loadtxt(file1)
    x1=np.linspace(0,1,len(data1))
    plt.plot(x1,data1,label="Euler-upwind with t=0.0476")
with open('q1_b_1024_0.047600.txt','r') as file2:
    data2=np.loadtxt(file2)
    x2=np.linspace(0,1,len(data2))
    plt.plot(x2,data2,label="Euler-central difference with t=0.0476") 

plt.xlabel("x")
plt.ylabel("u")
plt.title("comparison for u vs x for N=1024 with alpha=0.001 and 0")
plt.legend()

# Show plot
plt.show()    