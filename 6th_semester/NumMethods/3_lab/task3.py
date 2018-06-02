import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv


def get_points():
    x = list(map(float, input().split()))
    y = list(map(float, input().split()))

    return x, y


def lls(k, x, y):
    x = np.array(x)
    t = np.array([[i ** j for i in x] for j in reversed(range(k))])
    t_trans = np.transpose(t)
    g = t @ t_trans
    a = inv(g) @ t @ y

    return a


def calc_err(x, y, coeff):
    y_err = [np.polyval(coeff, i) for i in x]

    err = sum([(y_err[idx] - i) ** 2 for idx, i in enumerate(y)])

    return err


def main():
    x, y = get_points()

    coef_2d = lls(2, x, y)
    print(coef_2d)
    coef_3d = lls(3, x, y)
    print(coef_3d)
    x_vals = np.linspace(x[0], x[-1])
    y_2d = [np.polyval(coef_2d, i) for i in x_vals]
    y_3d = [np.polyval(coef_3d, i) for i in x_vals]

    plt.scatter(x, y, color='r')
    plt.plot(x_vals, y_2d, color='b')
    plt.plot(x_vals, y_3d, color='g')
    plt.show()
    print(f'error for ax + b = {calc_err(x, y, coef_2d)}')
    print(f'error for ax^2 + bx + c = {calc_err(x, y, coef_3d)}')


main()