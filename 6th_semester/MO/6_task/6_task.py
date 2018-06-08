from scipy.optimize import minimize
import numpy as np
from numpy.linalg import norm
import sys

def func(N, vec):
    x1, x2 = vec
    return  2 * N * x1 * x1 + 3 * N * x2 * x2 - 8 * N * x1 + 6 * N * x2 + 7


def gradient(N, vec):
    x1, x2 = vec
    return [4 * N * x1 - 8 * N, 6 * N * x2 + 6 * N]


def main():
    N = int(sys.argv[1])
    M = int(sys.argv[2])
    x = [0.0, 0.0]
    eps = 0.9
    x_series = [x]
    n = len(x)
    res = np.inf
    last_succ_iter = -2
    was_check_succ = False

    for j in range(M):
        print(f'j = {j}')

        for k in range(n):
            print(f'k = {k}')

            last_x = x_series[-1]
            print(f'x[{j}][{k}] = {last_x}')
            norm_grad = norm(gradient(N, last_x))
            print(f'||grad(f(x))|| = {norm_grad}')
            if norm_grad < eps:
                res = last_x
                print(f'norm of gradient is < eps.\nResult is:\n{res}')
                print(f'series:\n{x_series}')
                exit()

            e_vec = np.zeros(n)
            e_vec[k] = 1.0
            grad_deriv = gradient(N, last_x)[k]
            print(grad_deriv)
            param_f = lambda t : func(N, last_x - t * grad_deriv * e_vec)

            t_opt = float(minimize(param_f, [0]).x)
            print(f't* = {t_opt}')

            new_x = last_x - t_opt * grad_deriv * e_vec
            print(f'x[{j}][{k + 1}] = {new_x}')
            x_series.append(new_x)

            vec_diff_norm = norm(new_x - last_x)
            func_diff_norm = norm(func(N, new_x) - func(N, last_x))
            print(f'||x[{j}][{k + 1}] - x[{j}][{k}]|| = {vec_diff_norm}')
            print(f'||f(x[{j}][{k + 1}]) - f(x[{j}][{k}])|| = {func_diff_norm}')
            if  vec_diff_norm < eps and func_diff_norm < eps:
                print(f"check in iteration {j} is ok")
                was_check_succ = True
            else:
                print(f"check in iteration {j} failed")
                was_check_succ = False

        if was_check_succ == True:
            if j - 1 == last_succ_iter:
                res = x_series[j + 1]
                print(f'result is {res}')
                print(f'series:\n{x_series}')
                exit()
            else:
                last_succ_iter = j
        print()

    print("Couldn't find solution")


if __name__ == "__main__":
    main()