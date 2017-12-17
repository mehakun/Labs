from matplotlib import pyplot as plot
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys
from nurbs import Surface as ns
from nurbs import utilities as utils
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from PyQt5.QtWidgets import QDialog, QApplication, QLabel, QVBoxLayout, QSlider
# Could not find qt.alignment
from PyQt5.QtCore import *

# Hello Im useful
def nurbs_point(p, coeff, t):
    if t >= len(p):
        return p[-1]
    i = int(t)
    t %= 1.
    dist = sqrt(sum((p[min(i+1, len(p)-1)][j]-p[max(0, i-1)][j])**2 for j in range(0, 3)))
    m = [(1 - coeff)*(p[min(i+1, len(p)-1)][j]-p[max(0, i-1)][j])  for j in range(0, 3)]
    dist = sqrt(sum((p[min(i+1, len(p)-1)][j]-p[max(0, i)][j])**2 for j in range(0, 3)))
    return [p[i][j]*(1 + 2*t**3 - 3*t**2) +
            m[j]*(t**3 - 2*t**2+t)*dist  + p[i+1][j]*(3*t**2 - 2*t**3) +
            m[j]*(t**3 - t**2)*dist
            for j in range(0, 3)]

def get_coords(surf, coeff):
    cnt = 0
    # Arrange calculated surface data for plotting
    surfpts_x = []
    surfpts_y = []
    surfpts_z = []

    pts_amount = len(surf.surfpts)

    for i in range(0, pts_amount, coeff):
        x_avg = []
        y_avg = []
        z_avg = []

        for j in range(i, i + coeff):
            if (j == pts_amount):
                break

            x_avg.append(surf.surfpts[j][0])
            y_avg.append(surf.surfpts[j][1])
            z_avg.append(surf.surfpts[j][2])

        surfpts_x.append(np.mean(x_avg))
        surfpts_y.append(np.mean(y_avg))
        surfpts_z.append(np.mean(z_avg))

        cnt += 1

    print("{} drawn".format(cnt))

    return (surfpts_x, surfpts_y, surfpts_z)

class Window(QDialog):
    def __init__(self, parent=None):
        super(Window, self).__init__(parent)

        # Create a NURBS surface instance
        self.surf = ns.Surface()

        # Set up the NURBS surface
        self.surf.read_ctrlpts("data.txt")
        self.surf.degree_u = 3
        self.surf.degree_v = 3
        self.surf.knotvector_u = [0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 3.0, 3.0, 3.0]
        self.surf.knotvector_v = [0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 3.0, 3.0, 3.0]

        # Calculate surface points
        self.surf.evaluate_rational()

        self.coeff = 10

        # A figure instance to plot on
        self.figure = plot.figure(figsize=(10.67, 8), dpi=96)

        # This is the Canvas Widget that displays the `figure`
        # it takes the `figure` instance as a parameter to __init__
        self.canvas = FigureCanvas(self.figure)

        # This is the Navigation widget
        # it takes the Canvas widget and a parent
        self.toolbar = NavigationToolbar(self.canvas, self)

        # Just some slider connected to `plot` method
        self.slider = QSlider(Qt.Horizontal)
        self.slider.setMinimum(1)
        self.slider.setMaximum(36)
        self.slider.setValue(10)
        self.slider.valueChanged.connect(self.plot)

        self.label = QLabel("Quality of drawing slider (left is best right is worst)")
        self.label.setAlignment(Qt.AlignCenter)

        # Set the layout
        layout = QVBoxLayout()
        layout.addWidget(self.toolbar)
        layout.addWidget(self.canvas)
        layout.addWidget(self.label)
        layout.addWidget(self.slider)
        self.setLayout(layout)

    def plot(self):
        # We are called by signal so value is actual
        self.coeff = self.slider.value()

        # Clear dem drawings
        self.figure.clear()

        # Get dem axises
        axises = self.figure.gca(projection='3d')

        # Get dem coords vectors
        X, Y, Z = get_coords(self.surf, self.coeff)

        # Set the plot env
        surf_plot = axises.plot(X, Y, Z, color="green")  # 3D Tri-Surface plot
        axises.set_xlim(-25, 25)
        axises.set_ylim(-25, 25)
        axises.set_zlim(-15, 15)

        # refresh canvas
        self.canvas.draw()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    main = Window()
    main.show()
    main.plot()

    sys.exit(app.exec_())