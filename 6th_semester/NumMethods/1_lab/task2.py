import numpy as np
import math

def ReadMatrixAndVec():
    matrixSize = int(input())

    matrix = [list(map(float, input().split())) for i in range(matrixSize)]
    vec = list(map(float, input().split()))

    return matrix, vec


def GetDiagsFromTridiagMatrix(matrix):
    aVec = [matrix[i][0] for i in range(1, len(matrix))]

    bVec = [matrix[i][1] for i in range(1, len(matrix))]
    bVec.insert(0, matrix[0][0])

    cVec = [matrix[i][2] for i in range(1, len(matrix) - 1)]
    cVec.insert(0, matrix[0][1])

    return aVec, bVec, cVec

def GetPV(aVec, bVec, cVec, xVec):
    pVec = [0 for i in range(len(bVec))]
    qVec = pVec.copy()
    pVec[0] = -cVec[0] / bVec[0]
    qVec[0] = xVec[0] / bVec[0]

    for i in range(1, len(bVec) - 1):
        pVec[i] =  -cVec[i] / (bVec[i] + aVec[i - 1] * pVec[i - 1])

        qVec[i] = (xVec[i] - aVec[i - 1] * qVec[i - 1]) / (bVec[i] + aVec[i - 1] * pVec[i - 1])


    qVec[-1] = (xVec[-1] - aVec[-1] * qVec[-2]) / (bVec[-1] + aVec[-1] * pVec[-2])

    return pVec, qVec

def SolveSLAU(pVec, qVec):
    xVec = qVec.copy()

    for i in reversed(range(len(qVec) - 1)):
        xVec[i] = pVec[i] * xVec[i + 1] + qVec[i]

    return xVec

def TridiagMatrixAlg(matrix, vec):
    aVec, bVec, cVec = GetDiagsFromTridiagMatrix(matrix)

    print("a diagonal:")
    print(np.matrix(aVec).transpose())
    print("b diagonal:")
    print(np.matrix(bVec).transpose())
    print("c diagonal:")
    print(np.matrix(cVec).transpose())
    print("Vector:")
    print(np.matrix(vec).transpose())

    pVec, qVec = GetPV(aVec, bVec, cVec, vec)

    print("P vector:")
    print(np.matrix(pVec).transpose())
    print("Q vector:")
    print(np.matrix(qVec).transpose())

    result = SolveSLAU(pVec, qVec)

    return result

if __name__ == "__main__":
    matrix, vec = ReadMatrixAndVec()

    res = TridiagMatrixAlg(matrix, vec)

    print("Result vector:")
    print(np.matrix(res).transpose())


