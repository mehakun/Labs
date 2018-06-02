import numpy as np
import matplotlib.pyplot as plt


def get_points():
    x_start = float(input())
    x = list(map(float, input().split()))
    y = list(map(float, input().split()))

    return x_start, x, y


def find_good_range_idx(x_start, x):
    k = 0
    for i, j in zip(x, x[1:]):
        if i <= x_start <= j:
            break
        k += 1

    return k


def calc_first_deriv(x, y, x_start):
    good_idx = find_good_range_idx(x_start, x)

    num1 = (y[good_idx + 1] - y[good_idx]) / (x[good_idx + 1] - x[good_idx])
    num2 = (y[good_idx + 2] - y[good_idx + 1]) / (x[good_idx + 2] - x[good_idx + 1]) - num1
    num2 = num2 / (x[good_idx + 2] - x[good_idx])

    return num1 + num2 * (2 * x_start - x[good_idx] - x[good_idx + 1])


def calc_second_deriv(x, y, x_start):
    good_idx = find_good_range_idx(x_start, x)
    num1 = (y[good_idx + 2] - y[good_idx + 1]) / (x[good_idx + 2] - x[good_idx + 1])
    num2 = (y[good_idx + 1] - y[good_idx]) / (x[good_idx + 1] - x[good_idx])

    return 2 * (num1 - num2) / (x[good_idx + 2] - x[good_idx])


def main():
    x_start, x, y = get_points()

    first_der = calc_first_deriv(x, y, x_start)
    second_der = calc_second_deriv(x, y, x_start)

    print(f'y\'(x) = {first_der}')
    print(f'y\"(x) = {second_der}')

main()