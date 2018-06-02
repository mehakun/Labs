import numpy as np
import matplotlib.pyplot as plot


def tma(matrix, d, shape):
    a, b, c = zip(*matrix)
    p = [-c[0] / b[0]]
    q = [d[0] / b[0]]
    x = [0] * (shape + 1)
    for i in range(1, shape):
        p.append(-c[i] / (b[i] + a[i] * p[i - 1]))
        q.append((d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]))
    for i in reversed(range(shape)):
        x[i] = p[i] * x[i + 1] + q[i]
    return x[:-1]


def spline(x, f):
    n = len(x)
    h = [x[i] - x[i - 1] for i in range(1, n)]
    tridiag_matrix = [[0, 2 * (h[0] + h[1]), h[1]]]
    b = [3 * ((f[2] - f[1]) / h[1] - (f[1] - f[0]) / h[0])]
    for i in range(1, n - 3):
        tridiag_row = [h[i], 2 * (h[i] + h[i + 1]), h[i + 1]]
        tridiag_matrix.append(tridiag_row)
        b.append(3 * ((f[i + 2] - f[i + 1]) / h[i + 1] - (f[i + 1] - f[i]) / h[i]))
    tridiag_matrix.append([h[-2], 2 * (h[-2] + h[-1]), 0])
    b.append(3 * ((f[-1] - f[-2]) / h[-1] - (f[-2] - f[-3]) / h[-2]))
    c = tma(tridiag_matrix, b, n - 2)
    a = []
    b = []
    d = []
    c.insert(0, 0)
    for i in range(1, n):
        a.append(f[i - 1])
        if i < n - 1:
            d.append((c[i] - c[i - 1]) / (3 * h[i - 1]))
            b.append((f[i] - f[i - 1]) / h[i - 1] -
                     h[i - 1] * (c[i] + 2 * c[i - 1]) / 3)
    b.append((f[-1] - f[-2]) / h[-1] - 2 * h[-1] * c[-1] / 3)
    d.append(-c[-1] / (3 * h[-1]))
    return a, b, c, d


def get_points():
    n = int(input())
    x = list(map(float, input().split()))
    f = list(map(float, input().split()))
    x_test = float(input())

    return x, f, x_test


def polyval(x0, x, k, coef):
    a, b, c, d = coef
    diff = x0 - x[k]

    return a[k] + b[k] * diff + c[k] * diff ** 2 + d[k] * diff ** 3


def poly(x, x_test, coef):
    k = 0
    for i, j in zip(x, x[1:]):
        if i <= x_test <= j:
            break
        k += 1

    return polyval(x_test, x, k, coef)


def main():
    x, f, x_test = get_points()
    coef = spline(x, f)

    res = poly(x, x_test, coef)
    print(f'x* = {x_test}')
    print(f'f(x*) = {res}')

    x_vals = np.linspace(x[0], x[-1])
    y = [poly(x, val, coef) for val in x_vals]

    plot.figure()
    plot.xlabel('x')
    plot.ylabel('y')
    plot.plot(x_vals, y, 'g')
    plot.grid(True)
    plot.show()

if __name__ == "__main__":
    main()
