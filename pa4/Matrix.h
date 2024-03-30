/**
 * Matrix.h
 * CSE 101 PA4
 * Zihua Li, CruzID: zli487
 **/

#include "List.h"

typedef struct MatrixObj {
    List* Entries_Row;
    /*
    An array of List ADTs that, each List ADT possesses the Entry ADTs, of the List ADT's corresponding row.
    The index of this array represents row index.
    */
    int Size;
    int NNZ;
} MatrixObj;

typedef struct MatrixObj* Matrix;

Matrix newMatrix(int n);

void freeMatrix(Matrix* pM);

int size(Matrix M);

int NNZ(Matrix M);

int equals(Matrix A, Matrix B);

void makeZero(Matrix M);

void changeEntry(Matrix M, int i, int j, double x);

Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix A);

Matrix sum(Matrix A, Matrix B);

Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

void printMatrix(FILE* out, Matrix M);