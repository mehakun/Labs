import numpy as np
import math

def ReadPrecision():
    return float(input())

def ReadMatrixAndVec():
    matrixSize = int(input())

    matrix = [list(map(float, input().split())) for i in range(matrixSize)]
    vec = list(map(float, input().split()))

    return matrix, vec

def TransformSLAU(matrix, vec):
    newMatrix = [[-matrix[i][j] / matrix[i][i] for j in range(len(matrix))] for i in range(len(matrix))]
    for i in range(len(matrix)):
        newMatrix[i][i] = 0

    newVec = [vec[i] / matrix[i][i] for i in range(len(matrix))]

    return newMatrix, newVec

def CalcNorm(matrix):
    return np.linalg.norm(matrix, np.inf)

def IsClosePrec(a, b):
    print("eps_k {}, user_eps {}".format(a, b))
    return a <= b

def CalcCurPrec(firstVec, secondVec, coeff):
    lul = CalcNorm(secondVec - firstVec)

    return lul * coeff

def zeidelCoeff(upperDiagMtx, mtx):
    return CalcNorm(upperDiagMtx) / (1 - CalcNorm(mtx))

def SolveSLAU(matrix, vec, prec, isJacobi):
    mtxT, vecT = TransformSLAU(matrix, vec)

    if isJacobi and CalcNorm(mtxT) >= 1:
        print("unsolvable with Jacobi\'s method")
        ("Sorry", "Nothing")
    
    origVec = np.matrix(vecT.copy()).transpose()
    matrixInNP = np.matrix(mtxT)
    solFirst = origVec.copy()
    solSecond = solFirst.copy()
    matrixNorm = CalcNorm(matrix)
    iterCounter = 0
    
    coeff = matrixNorm / (1 - matrixNorm)  if isJacobi else zeidelCoeff(np.triu(matrixInNP), matrixInNP)

    while True:
        if isJacobi:
            solSecond = origVec + matrixInNP @ solFirst
        else:
            for i in range(len(origVec)):
                solSecond[i][0] = origVec.item(i, 0) + math.fsum([matrixInNP.item(i, j) * solFirst.item(j, 0) for j in range(len(origVec))])

        if (IsClosePrec(CalcCurPrec(solFirst, solSecond, coeff), prec)):
            break

        solFirst = solSecond.copy()
        iterCounter += 1

    return solSecond, iterCounter

if __name__ == "__main__":
    precision = ReadPrecision()
    matrix, vec = ReadMatrixAndVec()

    print("Solving SLAU with Jacobi:")
    resJac, jacIters = SolveSLAU(matrix, vec, precision, isJacobi=True)

    print("Solving SLAU with Zeidel:")
    resZeid, zeidIters = SolveSLAU(matrix, vec, precision, isJacobi=False)
    print("\nepsilon is {}".format(precision))
    print("Jacobi method result:\n{}\n in {} iterations".format(resJac, jacIters))
    print("Zeidel method result:\n{}\n in {} iterations".format(resZeid, zeidIters))

    print("Original vector:\n{}\nOriginal vector after Jacobi:\n{}\nOriginal vector after Zeidel:\n{}".format(np.matrix(vec).transpose(),
                                                                                                              np.matrix(matrix) @ resJac,
                                                                                                              np.matrix(matrix) @ resZeid))

