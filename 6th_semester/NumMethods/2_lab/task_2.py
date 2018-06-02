import numpy as np
import matplotlib.pyplot as plot
import math


def jacobi(x):
    x1, x2 = x

    return np.array([[1, math.sin(x2)], [-math.cos(x1), 1]])


def func(x):
    x1, x2 = x

    return np.array([x1 - math.cos(x2) - 1, x2 - math.sin(x1) - 1])


def find_delta_x(f, J):
    return np.linalg.solve(J, -1 * f) 


def newthon(x_start, eps):
    x_curr = x_start
    x_next = []
    iters = 0
    is_close = False

    while True:
        print(f'x_{iters} = \n{x_curr}')

        f_x = func(x_curr)
        J_x = jacobi(x_curr)
        print(f'f(x_{iters}) = \n {f_x}')
        print(f'J(x_{iters}) = \n {J_x}')

        x_next = x_curr + find_delta_x(f_x, J_x)

        print(f'x_{iters + 1} = \n{x_next}')

        diff = np.linalg.norm(x_next - x_curr, ord=np.inf)
        print(f'||x_{iters + 1} - x_{iters}|| = {diff}')

        if diff <= eps:
            print(f'Found solution in {iters} steps')
            break

        x_curr = x_next
        iters += 1

    return x_next, iters


def ph(x):
    x1, x2 = x

    return np.array([[1 + math.cos(x2)], [1 + math.sin(x1)]])


def ph_der(x):
    x1, x2 = x

    return np.array([[0, -math.sin(x2)], [math.cos(x1), 0]])


def simple_iters(x_range, phi, phi_deriv, eps):
    x_curr = np.array([[np.mean(x)] for x in x_range])
    x_next = []
    iters = 0
    print(f'x is = {x_range}')
    x_series = [np.linspace(x[0], x[1]) for x in x_range]

    q = max(map(lambda x: np.linalg.norm(phi_deriv(x), ord=np.inf), zip(*x_series)))
    print(f'q = {q}')
    if q >= 1:
        print("q should be < 1")
        exit()

    coeff = q / (1 - q)
    print(f'coeff = {coeff}')
    while True:
        print(f'x_{iters} = \n{x_curr}')

        x_next = phi(x_curr)

        print(f'x_{iters + 1} = \n{x_next}')

        diff = np.linalg.norm(x_next - x_curr, ord=np.inf) * coeff
        print(f'||x_{iters + 1} - x_{iters}|| * coeff = {diff}')

        if diff <= eps:
            print(f'Found solution in {iters} steps')
            break

        x_curr = x_next
        iters += 1

    return x_next, iters


def main():
    # x_series = np.arange(-3.0, 3.1, 0.1)
    # f1_series = [(lambda x2: math.cos(x2) + 1)(x) for x in x_series]
    # f2_series = [(lambda x1: math.sin(x1) + 1)(x) for x in x_series]

    # plot.figure()
    # plot.xlabel('x1')
    # plot.ylabel('x2')
    # plot.plot(x_series, f1_series, 'r')
    # plot.plot(f2_series, x_series,'g')
    # plot.axis('equal')
    # plot.grid(True)
    # plot.show()

    # 1.5 <= x1 <= 2
    # 0.7 <= x2 <= 0.92
#    (1.73, 0.83)
    eps = float(input())
    x_start = np.array([[1.7], [0.75]])

    root_n, iters_n = newthon(x_start, eps)

    x_range = [(1.7, 1.8), (0.75, 0.85)]
    root_si, iters_si = simple_iters(x_range, ph, ph_der, eps)

    print(f'Newthon: root is:\n{root_n}\nfound in {iters_n} iterations')
    print(f'Simple iterations: root is:\n{root_si}\nfound in {iters_si} iterations')

    print(f'Are roots close? {np.allclose(root_n, root_si, atol=eps)}')

main()