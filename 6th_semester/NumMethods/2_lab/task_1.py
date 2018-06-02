import numpy as np
import matplotlib.pyplot as plot
import math


def func(x):
    return math.sin(x) - 2 * x * x + 0.5


def first_func(x):
    return math.sin(x)


def second_func(x):
    return 2 * x * x - 0.5


def lin_func(x):
    return math.sqrt((math.sin(x) + 0.5) / 2.0)


def lin_deriv(x):
    return math.cos(x) / math.sqrt((math.sin(x) + 0.5) * 8)


def simple_iter(root_range, eps, sign):
    begin, end = root_range
    print(f'Lurking for root in {root_range}')

    q = max([abs(lin_deriv(x)) for x in np.arange(begin, end, eps)])
    print(f'q = {q}')

    if q >= 1.0:
        print(f'bad range, q = {q}! It should be < 1 exiting!')
        exit()

    coeff = q / (1 - q)
    print(f'coeff = {coeff}')
    iters = 1

    x_prev = (begin + end) / 2.0
    print(f'x_{iters - 1} = {x_prev}')
    x_cur = lin_func(x_prev) * sign
    diff = abs(x_cur - x_prev) * coeff
    print(f'|x_{iters} - x_{iters - 1}| * coeff = {diff}')

    while diff >= eps:
        x_prev = x_cur
        x_cur = lin_func(x_prev) * sign
        iters += 1
        print(f'x_{iters - 1} = {x_prev}')
        print(f'x_{iters} = {x_cur}')
        diff = abs(x_cur - x_prev) * coeff
        print(f'|x_{iters} - x_{iters - 1}| * coeff = {diff}')

    return x_cur, iters


def newthon_solve(root_range, start_x, first_deriv, second_deriv, eps):
    begin, end = root_range

    if func(begin) * func(end) >= 0:
        print(f'f(a)f(b) = {func(begin) * func(end)}\n It should be < 0')
        exit()

    if func(start_x) * second_deriv(start_x) <= 0:
        print(f'f(x_0)f\"(x_0) = {func(start_x) * second_deriv(start_x)}\n It should be > 0')
        exit()

    iters = 1
    x_prev = start_x
    x_cur = x_prev - func(x_prev) / first_deriv(x_prev)
    diff = abs(x_cur - x_prev)
    print(f'x_{iters - 1} = {x_prev}')
    print(f'x_{iters} = {x_cur}')
    print(f'|x_{iters} - x_{iters - 1}| = {diff}')

    while diff >= eps:
        x_prev = x_cur
        x_cur = x_prev - func(x_prev) / first_deriv(x_prev)
        diff = abs(x_cur - x_prev)
        iters += 1

        print(f'x_{iters - 1} = {x_prev}')
        print(f'x_{iters} = {x_cur}')
        print(f'|x_{iters} - x_{iters - 1}| = {diff}')

    return x_cur, iters


def main():
    eps = float(input())
    # x_series = np.arange(-1.0, 1.1, 0.1)
    # f1_series = [first_func(x) for x in x_series]
    # f2_series = [second_func(x) for x in x_series]

    # plot.figure()
    # plot.xlabel('x')
    # plot.ylabel('y')
    # plot.plot(x_series, f1_series, 'r')
    # plot.plot(x_series, f2_series, 'g')
    # plot.axis([-1, max(x_series), min(f1_series + f2_series), max(f1_series + f2_series)])
    # plot.grid(True)
    # plot.show()

    # x_1 = -0.308
    # y_1 = -0.308
    # x_2 = 0.775
    # y_2 = 0.693
    root_ranges = [((-0.35, -0.25), -1), ((0.75, 0.88), 1)]

    for rnge in root_ranges:
        bound, sign = rnge
        res_s, iter_count = simple_iter(bound, eps, sign)
        print("Simple iterations:\n")
        print(f'Found solution in range {bound}:\n{res_s}\nIn {iter_count} iterations\n')

        print("Newthon:\n")
        res_n, iter_count = newthon_solve(bound, max(bound, key=abs), lambda x: math.cos(x) - 4 * x, lambda x: -math.sin(x) - 4, eps)
        print(f'Found solution in range {bound}:\n{res_n}\nIn {iter_count} iterations\n')

        print(f'Are they close? {math.isclose(res_n, res_s, abs_tol=eps)}')

main()