import numpy as np

def simpson(interval, f, n):
    a, b = interval
    x = np.linspace(a, b, 2 * n)

    f_i = lambda i: f(a + (i * (b - a)) / (2 * n))
    first_part = 4 * np.sum([f_i(i) for i in range(1, 2 * n, 2)])
    second_part = 2 * np.sum([f_i(i) for i in range(2, 2 * n - 1, 2)])
    integral = (b - a) / (6 * n) * (f_i(0) + first_part + second_part + f_i(2 * n))

    return integral


def monte_karlo(intervals, f, size, experiments_amount):
    lower = [interval[0] for interval in intervals]
    upper = [interval[1] for interval in intervals]
    coeff = np.prod([b - a for a, b in intervals]) / experiments_amount
    integral = coeff * np.prod([f(np.random.uniform(lower, upper, size)) for _ in range(experiments_amount)])

    return integral


