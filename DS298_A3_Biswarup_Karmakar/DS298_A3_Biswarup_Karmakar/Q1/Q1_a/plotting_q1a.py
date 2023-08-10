import numpy as np
import matplotlib.pyplot as plt

# Values of j
j_values = ["0.004000","0.014400","0.028800","0.047600","0.075000"]

# Loop over j values
for t in j_values:
    # Read data from output file
    filename = "q1_a_64_" + str(t) + ".txt"
    data = np.loadtxt(filename)
    x = np.linspace(0, 1, len(data))
    u = data

    # Plot u vs x
    plt.plot(x, u, label="t = " + str(t))

# Add axis labels and legend
plt.xlabel("x")
plt.ylabel("u")
plt.title("u vs x for N=64")
plt.legend()

# Show plot
plt.show()



# Loop over j values
for t in j_values:
    # Read data from output file
    filename = "q1_a_1024_" + str(t) + ".txt"
    data = np.loadtxt(filename)
    x = np.linspace(0, 1, len(data))
    u = data

    # Plot u vs x
    plt.plot(x, u, label="t = " + str(t))

# Add axis labels and legend
plt.xlabel("x")
plt.ylabel("u")
plt.title("u vs x for N=1024")
plt.legend()

# Show plot
plt.show()