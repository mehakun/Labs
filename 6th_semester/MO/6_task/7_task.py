from scipy.optimize import minimize
import numpy as np
from numpy.linalg import norm, inv
import sys

def func(N, vec):
    x1, x2 = vec
    return  2 * N * x1 * x1 + 3 * N * x2 * x2 - 8 * N * x1 + 6 * N * x2 + 7


def gradient(N, vec):
    x1, x2 = vec
    return [4 * N * x1 - 8 * N, 6 * N * x2 + 6 * N]


def hessian(N, vec):
    return np.array([[4 * N, 0.0], [0.0, 6 * N]])


def is_pos_def(A):    
    try:
        np.linalg.cholesky(A)
        return True
    except LinAlgError:
        return False
        

def main():
    N = int(sys.argv[1])
    M = int(sys.argv[2])
    x_curr = [0.0, 0.0]
    x_next = x_curr.copy()
    res = x_next.copy()
    hess = []
    eps = 0.9
    was_first_check_succ = False

    for k in range(M):
        x_curr = x_next
        print(f'x_{k} = {x_curr}')
        grad = gradient(N, x_curr)
        print(f'grad(f(x_{k})) = {grad}')
        norm_grad = norm(grad)
        print(f'||grad(f(x_{k}))|| = {norm_grad}')
        if norm_grad <= eps:
            res = x_curr
            print(f'norm of gradient is < eps.\nResult is:\n{res}')
            break

        hess = hessian(N, x_curr)
        print(f'H(x) =\n{hess}')
        hess_inv = inv(hess)
        print(f'H(x)^(-1) =\n{hess_inv}')
        d = grad
        t = np.inf

        if is_pos_def(hess_inv):
            print(f'H(x) > 0')
            d = -hess_inv @ grad
            t = 1.0

        else:
            print(f'H(x) ≯ 0')
            d = -grad
            param_f = lambda t: func(N, x_curr + t * d)
            t = minimize(param_f, x_curr).x

        print(f'd = {d}\nt = {t}')
        x_next = x_curr + t * d
        print(f'x_{k + 1} = {x_next}')

        vec_diff_norm = norm(x_next - x_curr)
        print(f'||x_{k + 1} - x_{k}|| = {vec_diff_norm}')
        func_diff_norm = norm(func(N, x_next) - func(N, x_curr))
        print(f'||f(x_{k + 1}) - f(x_{k})|| = {func_diff_norm}')

        if  vec_diff_norm < eps and func_diff_norm < eps:
            if was_first_check_succ == False:
                print("First check passed")
                was_first_check_succ = True
            elif was_first_check_succ == True:
                res = x_next
                print(f'Second check passed result is:\n{res}')
                exit()
            else:
                print("First check failed")
                was_first_check_succ = False

    exit()


if __name__ == "__main__":
    main()