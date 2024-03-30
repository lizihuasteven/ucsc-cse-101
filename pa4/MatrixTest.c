/**
 * MatrixTest.c
 * CSE 101 PA4
 * Zihua Li, CruzID: zli487
 **/

#include "Matrix.h"
#include <assert.h>
#include <stdio.h>

int main() {
    Matrix M, N, P, Q, R;

    M = newMatrix(5);
    assert(size(M) == 5);
    assert(NNZ(M) == 0);

    // Test changeEntry
    changeEntry(M, 1, 1, 5);
    assert(NNZ(M) == 1);

    // Test copy
    N = copy(M);
    assert(equals(M, N));

    // Test scalarMult
    N = scalarMult(2, M);
    changeEntry(M, 1, 1, 10);
    assert(equals(M, N));

    // Test sum
    makeZero(N);
    changeEntry(N, 1, 1, 5);
    P = sum(M, N);
    assert(NNZ(P) == 1);

    // Test diff
    Q = diff(M, N);
    changeEntry(N, 1, 1, 5);
    assert(equals(Q, N));

    // Test transpose
    R = transpose(M);

    // Test transpose result
    makeZero(N);
    changeEntry(N, 1, 1, 10);
    assert(equals(N, R));

    // Test product
    makeZero(M);
    makeZero(N);
    changeEntry(M, 1, 1, 5);
    changeEntry(N, 1, 1, 5);
    P = product(M, N);

    // Test product result
    makeZero(R);
    changeEntry(R, 1, 1, 25);
    assert(equals(P, R));

    // Free matrices
    freeMatrix(&M);
    freeMatrix(&N);
    freeMatrix(&P);
    freeMatrix(&Q);
    freeMatrix(&R);

    printf("All tests passed!\n");

    return 0;
}