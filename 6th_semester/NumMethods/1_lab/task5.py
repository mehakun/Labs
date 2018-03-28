import numpy as np
import math
from copy import deepcopy
from numpy.linalg import norm, eig
import functools


def PrintStep(stepName):
    print("\n------------------------------\n{}\n------------------------------\n".format(stepName))


def ReadPrecision():
    return float(input())


def ReadMatrix():
    matrixSize = int(input())

    matrix = [list(map(float, input().split())) for i in range(matrixSize)]

    return matrix


def MakeHouseholder(column, iteration):
    v = np.zeros(len(column))

    v[iteration] = column[iteration] + np.sign(column[iteration]) * norm(column[iteration:])
    for i in range(iteration + 1, len(column)):
        v[i] = column[i]
    h = np.eye(len(column)) - (2 / (v @ v)) * (v[:, None] @ v[None, :])

    return h


def MakeQRDecomposition(matrix):
    PrintStep("QR Decomposition")
    qMatrix = np.eye(len(matrix))
    rMatrix = matrix.copy()

    for i in range(len(matrix) - 1):
        print("QR step number {}".format(i))
        house = MakeHouseholder(rMatrix[:, i], i)
        print("householder matrix:\n{}".format(house))
        qMatrix = qMatrix @ house
        print("Q matrix:\n{}".format(qMatrix))
        rMatrix = house @ rMatrix
        print("R matrix:\n{}".format(rMatrix))

    return qMatrix, rMatrix


def FindEigens(mtx, idx):
    matrix = mtx.tolist()
    a11 = matrix[idx][idx]
    a12 = matrix[idx][idx + 1]
    a21 = matrix[idx + 1][idx]
    a22 = matrix[idx + 1][idx + 1]
    print("my beatifur submatrix:\n{} {}\n{} {}".format(a11, a12, a21, a22))
    return np.roots((1, -a11 - a22, a11 * a22 - a12 * a21))


def Check(matrix, eps):
    PrintStep("Checking if we are close")
    result = []
    idx = 0
    while idx < len(matrix):
        if norm(matrix[idx + 1:, idx]) <= eps:
            print("{} is good".format(matrix.item(idx, idx)))
            result.append(matrix.item(idx, idx))

        elif norm(matrix[idx + 2:, idx]) <= eps:
            roots = FindEigens(matrix, idx)
            print("these roots are stable:\n{}".format(roots))
            result.extend(roots)
            idx += 1

        idx += 1

    print("got something in the check:\n{}".format(result))
    if len(result) + 1 == len(matrix):
        print("!!!!ALERT!!!!check didnt find all eigen values!")
        #result.append(matrix.item(-1, -1))
        
    return result


def FindEigenValues(matrix, prec, maxSteps = math.inf):
    PrintStep("Finding eigen values")

    currMatrix = deepcopy(matrix)
    result = []
    iterCount = 0
    isCheckPassed = False

    while True and iterCount != maxSteps:
        qMatrix, rMatrix = MakeQRDecomposition(currMatrix)

        PrintStep("After QR decomp")
        print("iteration = {}".format(iterCount))
        print("Q matrix:\n{}".format(qMatrix))
        print("R matrix:\n{}".format(rMatrix))

        currMatrix = rMatrix @ qMatrix
        print("Current matrix:\n{}".format(currMatrix))
        result = Check(currMatrix, prec)
        print("current eigen values:\n{}".format(result))

        if len(result) == len(matrix):
            if isCheckPassed == False:
                isCheckPassed = True
            else:
                break
        iterCount += 1

    return result, iterCount


if __name__ == "__main__":
    prec = ReadPrecision()
    matrix = np.matrix(ReadMatrix())

    eVal, iterations = FindEigenValues(matrix, prec)
    eigenValues = sorted(eVal)
    npEigens = sorted(eig(matrix)[0])
    PrintStep("Found all eigen values")
    print("wasted {} iterations with precision {}".format(iterations, prec))
    print("final eigen values:\n{}".format(eigenValues))
    print("numpy found these eigens:\n{}".format(npEigens))
    print("Are they close?\n{}".format(np.isclose(eigenValues, npEigens, prec, prec)))
