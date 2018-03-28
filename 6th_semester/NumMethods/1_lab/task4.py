import numpy as np
import math
from copy import deepcopy
import time
import functools

def ReadPrecision():
    return float(input())

def ReadMatrix():
    matrixSize = int(input())

    matrix = [list(map(float, input().split())) for i in range(matrixSize)]

    return matrix

def MaxNonDiag(matrix):
    i, j = 0, 1

    maxVal = abs(matrix[0][1])

    for k in range(len(matrix)):
        for l in range(len(matrix)):
            if maxVal < abs(matrix[k][l]) and k != l:
                i, j = k, l

    return i, j

def CalcAngle(matrix, i, j):
    delimeter = matrix[i][i] - matrix[j][j]

    res = math.atan(2 * matrix[i][j] / delimeter) / 2.0 if delimeter != 0 \
          else math.pi / 4.0

    return res

def MakeOrthMtx(matrix, i, j):
    phiAngle = CalcAngle(matrix, i, j)
    orthMtx = [[0.0] * len(matrix) for k in range(len(matrix))]
    orthMtx[i][j] = -math.sin(phiAngle)
    orthMtx[j][i] = math.sin(phiAngle)
    orthMtx[i][i] = math.cos(phiAngle)
    orthMtx[j][j] = math.cos(phiAngle)
    for m in range(len(matrix)):
        if m != i and m != j:
            orthMtx[m][m] = 1.0

    return orthMtx

def QuadNonDiagSum(matrix):
    sum = 0.0

    for i in range(len(matrix)):
        sum += math.fsum([matrix[i][j] * matrix[i][j] if i != j 
                          else 0.0
                          for j in range(len(matrix))])

    return sum

def PrecFunc(matrix):
    return math.sqrt(QuadNonDiagSum(matrix))

def IsClose(iterEps, userEps):
    print("iteration eps = {}; user eps = {}".format(iterEps, userEps))

    return iterEps < userEps

def FindEigVec(matrix, eps):
    mtxFirst = np.transpose(deepcopy(matrix))
    mtxSecond = [[]]
    orthoList = []
    iteration = 0

    while True:
        maxI, maxJ = MaxNonDiag(mtxFirst)
#        print("max elem is {} with i = {}, j = {}".format(mtxFirst[maxI][maxJ], maxI, maxJ))
        orthMtx = MakeOrthMtx(mtxFirst, maxI, maxJ)
        orthoList.append(orthMtx)
        mtxSecond = np.dot(np.dot(np.transpose(orthMtx), mtxFirst), orthMtx)
#        print("ortho:\n{}\nfirst:\n{}\nsecond:\n{}".format(np.transpose(orthMtx), mtxFirst, mtxSecond))

        if IsClose(PrecFunc(mtxSecond), eps):
            break

        iteration += 1
        mtxFirst = deepcopy(mtxSecond)


    res = [mtxSecond[i][i] for i in range(len(matrix))]
    
    return res, iteration, functools.reduce(np.dot, orthoList)

if __name__ == "__main__":
    prec = ReadPrecision()
    mtx = ReadMatrix()

    eigVals, iterCount, eigVecs = FindEigVec(mtx, prec)
    
    print("Found Eigen values:\n{}\nAnd Eigen vectors:\n{}\n In {} iterations".format(";\n".join(map(str, eigVals)),
                                                                                      eigVecs,
                                                                                      iterCount))
    for i in range(len(mtx)):
        lhs = mtx @ eigVecs[:, i]
        rhs = eigVecs[:, i] * eigVals[i]
        print(lhs)
        print(rhs)
        print("{} eigenVals is {}".format(i, np.isclose(lhs, rhs, prec)))
