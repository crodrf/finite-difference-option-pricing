import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

# Load data and handle potential errors in file reading
try:
    x, y, z = np.loadtxt('fdm.csv', unpack=True)
except OSError:
    raise FileNotFoundError("The file 'fdm.csv' was not found. Ensure it is in the same directory as this script.")

# Reshape data for plotting
num_points = int(np.sqrt(len(x)))  # Assumes square grid based on provided shape
X = np.reshape(x, (num_points, num_points))
Y = np.reshape(y, (num_points, num_points))
Z = np.reshape(z, (num_points, num_points))

# Verify reshaped arrays for consistency
assert X.shape == Y.shape == Z.shape, "Reshaped arrays do not match expected grid dimensions."

# Create the figure and 3D axis
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Configure surface plot
surface = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.viridis, edgecolor='k', linewidth=0.5)
ax.set_zlim(0, 1.0)

# Axis labels
ax.set_xlabel(r'$S$ (Spot Price)', fontsize=12, labelpad=10)
ax.set_ylabel(r'$T - t$ (Time to Maturity)', fontsize=12, labelpad=10)
ax.set_zlabel(r'$C(S, t)$ (Option Price)', fontsize=12, labelpad=10)

# Add a color bar for reference
cbar = fig.colorbar(surface, shrink=0.5, aspect=10, pad=0.1)
cbar.set_label("Option Price", rotation=270, labelpad=15)

# Save plot to file instead of displaying it
plt.tight_layout()
plt.savefig("plot.png")  # Saves the plot as plot.png for artifact upload in CI
