import numpy

def F(m):
    x1 = (400 * m / 3 - 200) / (15 + 8 * m)
    x2 = (400 * m - 600) / (15 + 8 * m)
    print(f'x1 = {x1}')
    print(f'x2 = {x2}')
    f = 11 + 200 * x1 + 400 * x2 + 7.5 * x1 ** 2 + 2.5 * x2 ** 2
    return f + m * (x1 + x2 - 80 / 3) ** 2


def main():
    m = float(input())

    print(F(m))


main()
