import numpy as np
import math
from copy import deepcopy

def ReadMatrixAndVec():
    matrixSize = int(input())

    matrix = [list(map(float, input().split())) for i in range(matrixSize)]
    vec = list(map(float, input().split()))

    return matrix, vec

def swapLines(matrix, idxFrom, idxTo):
    matrix[idxFrom], matrix[idxTo] = matrix[idxTo], matrix[idxFrom]

def pivot(matrix):
    p = []
    mtrx = matrix.copy()
    for j in range(len(mtrx)):
        tmp = [(mtrx[i][j], i) for i in range(j, len(mtrx))]
        idx = max(tmp, key=lambda x: abs(x[0]))[1]
        if idx != j:
            p.append((j, idx))
            swapLines(mtrx, j, idx)
    return p, mtrx

def LUDecomp(matrix):
    shape = len(matrix)
    lower = np.zeros((shape, shape))
    upper = np.zeros((shape, shape))
    pivo, pMtx = pivot(matrix)

    for i in range(shape):
        lower[i][i] = 1.0

        for j in range(i + 1):
            upper[j][i] = pMtx[j][i] - math.fsum([lower[j][k] * upper[k][i] for k in range(j)])
        for j in range(i, shape):
            lower[j][i] = (pMtx[j][i] - math.fsum([lower[j][k] * upper[k][i] for k in range(i)])) / upper[i][i]

    return lower, upper, pivo

def DirectSubstit(lowerMatrix, valVec):
    res = deepcopy(valVec)

    for i in range(1, len(valVec)):
        res[i] = valVec[i] - math.fsum([lowerMatrix[i][j] * res[j] for j in range(i)])

    return res

def InverseSubstit(upperMatrix, valVec):
    res = [0 for i in range(len(valVec))]
    res[-1] = valVec[-1] / upperMatrix[-1][-1]

    for i in reversed(range(len(valVec) - 1)):
        res[i] = (valVec[i] - math.fsum([upperMatrix[i][j] * res[j] for j in range(i + 1, len(valVec))])) / upperMatrix[i][i]

    return res

def pivotVec(vec, pivo):
    res = vec.copy()

    for i in range(len(pivo)):
        fromIdx, toIdx = pivo[i]
        swapLines(res, fromIdx, toIdx)

    return res

def SolveSLAU(matrix, valVec, isSingle):
    lower, upper, pivo = LUDecomp(matrix)

    if isSingle:
        print("Lower:")
        print(lower)
        print("Upper:")
        print(upper)

    pVec = pivotVec(valVec, pivo)

    if isSingle:
        print("Pivoted vector:")
        print(pVec)

    rhsVec = DirectSubstit(lower, pVec)

    if isSingle:
        print("rhsVec:")
        print(rhsVec)

    solVec = InverseSubstit(upper, rhsVec)

    return solVec

def InverseMtx(matrix):
    res = [[] for i in range(len(matrix))]
    eVec = [0.0 for i in range(len(matrix))]

    for i in range(len(matrix)):
        eVec[i] = 1.0
        tmp = SolveSLAU(matrix, eVec, False)
        for j in range(len(tmp)):
            res[j].append(tmp[j])
        eVec[i] = 0

    return res

def submatrix(M, c):
    B = [[1] * len(M) for i in range(len(M))]

    for l in range(len(M)):
        for k in range(len(M)):
            B[l][k] = M[l][k]

    B.pop(0)

    for i in range(len(B)):
        B[i].pop(c)
    return B

def det(mtx):
    res = 0

    if len(mtx) <= 2:
        return mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0]
    else:
        for i in range(len(mtx)):
            res += ((-1) ** (i)) * mtx[0][i] * det(submatrix(mtx, i))

    return res

if __name__ == "__main__":
    matrix, vec = ReadMatrixAndVec()
    print("Orig Matrix:")
    print(matrix)
    print("valVec:")
    print(vec)

    result = np.matrix(SolveSLAU(matrix, vec, True)).transpose()
    npMtx = np.matrix(matrix)
    npVec = np.matrix(vec).transpose()

    print("Result:")
    print(result)
    print("matrix determinant:")
    print(det(matrix))
    print("matrix inverse:")
    print(np.matrix(InverseMtx(matrix)))
