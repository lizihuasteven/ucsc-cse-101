/**
 * Matrix.c
 * CSE 101 PA4
 * Zihua Li, CruzID: zli487
 **/

#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct EntryObj* Entry;

typedef struct EntryObj {
    double Value;
    int Column;
} EntryObj;

Entry newEntry(Matrix M, double Value, int Column) {
    Entry E = malloc(sizeof(EntryObj));
    E->Value = Value;
    E->Column = Column;
    //(Value != 0) ? M->NNZ++ : (void) 0;
    return E;
}

void freeEntry(Entry* pE) {
    if(pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->Entries_Row = malloc((n + 1) * sizeof(List));
    for (int i = 0; i <= n; i++) M->Entries_Row[i] = newList();
    M->Size = n;
    M->NNZ = 0;
    return M;
}

void freeMatrix(Matrix* pM) {
    if(pM != NULL && *pM != NULL) {
        for(int i = 0; i <= size(*pM); i++) {
            List L = (*pM)->Entries_Row[i];
            moveFront(L);
            while(index(L) >= 0) {
                Entry delEntry = get(L);
                //fflush(stdout);
                freeEntry(&delEntry);
                moveNext(L);
            }
            freeList(&((*pM)->Entries_Row[i]));
        }
        free((*pM)->Entries_Row);
        free(*pM);
        *pM = NULL;
        //pM = NULL;
    }
}

int size(Matrix M) {
    return M->Size;
}

int NNZ(Matrix M) {
    return M->NNZ;
}

int EntryCompare(EntryObj* entryA, EntryObj* entryB) {
    // Compare two EntryObjs, assuming EntryObj has a field 'value'
    // Adjust this as per actual 'EntryObj' definition
    if(entryA->Value == entryB->Value) {
        return 1;
    }
    else {
        return 0;
    }
}

int RowCompare(List rowA, List rowB) {
    // Comparing two rows of a given matrix.
    // Note: Modify the comparison logic based on actual structure of 'EntryObj'

    // check if lengths of both rows are equal
    if(length(rowA) != length(rowB)) {
        return 0;
    }

    moveFront(rowA);
    moveFront(rowB);

    while(index(rowA)!=-1 && index(rowB)!=-1)
    {
        if(!EntryCompare(get(rowA), get(rowB))) {
            return 0;
        }
        moveNext(rowA);
        moveNext(rowB);
    }

    return 1;
}

void printMatrixRow(List L) {
    if(L == NULL) {
        printf("Matrix Error: calling printMatrixRow() on NULL List reference");
        exit(1);
    }

    moveFront(L);
    while(index(L)>=0) {
        Entry e = (Entry)get(L); // Assuming that your list stores Entry type objects.
        printf(" value: %f, column: %d,", e->Value, e->Column);
        moveNext(L);
    }
    printf("\n");
}

int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Error: calling equals() on one or more NULL Matrices.\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
        return 0;
    }
    for (int i = 1; i <= size(A); i++) {
        List listA = A->Entries_Row[i];
        List listB = B->Entries_Row[i];
        if (length(listA) != length(listB)) {
            return 0;
        }
        moveFront(listA);
        moveFront(listB);
        while (index(listA) >= 0 && index(listB) >= 0) {
            Entry entryA = (Entry)get(listA);
            Entry entryB = (Entry)get(listB);
            if (entryA->Column != entryB->Column || entryA->Value != entryB->Value) {
                return 0;
            }
            moveNext(listA);
            moveNext(listB);
        }
    }
    return 1;
}

void makeZero(Matrix M) {
    for(int i = 0; i <= M->Size; i++) {
        List L = M->Entries_Row[i];
        while(length(L) > 0) deleteFront(L);
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    List L = M->Entries_Row[i];
    for(moveFront(L); index(L) >= 0; moveNext(L)) {
        Entry currentE = get(L);
        if(currentE->Column == j) {
            if(x != 0) {
                Entry E = newEntry(M, x, j);
                insertBefore(L, E);
                freeEntry(&currentE);
                delete(L);
                return;
            } else {
                freeEntry(&currentE);
                delete(L);
                (M->NNZ)--;
                return;
            }
            break;
        }
    }
    if(x == 0) return;
    moveFront(L);
    while(index(L) >= 0) {
        if(((Entry) get(L))->Column > j) break;
        moveNext(L);
    }
    (index(L) >= 0) ? insertBefore(L, newEntry(M, x, j)) : append(L, newEntry(M, x, j));
    (M->NNZ)++;
}

Matrix copy(Matrix A) {
    Matrix newM = newMatrix(A->Size);
    newM->NNZ = A->NNZ;

    for(int i = 0; i <= A->Size; i++) {
        List L = A->Entries_Row[i];
        for (moveFront(L); index(L) >= 0; moveNext(L)) {
            Entry E = get(L);
            Entry newE = newEntry(newM, E->Value, E->Column);
            append(newM->Entries_Row[i], newE);
        }
    }
    return newM;
}

Matrix transpose(Matrix A) {
    Matrix newM = newMatrix(A->Size);
    newM->NNZ = A->NNZ;

    for (int i = 0; i <= A->Size; i++) {
        List L = A->Entries_Row[i];
        for (moveFront(L); index(L) >= 0; moveNext(L)) {
            Entry E = get(L);
            Entry newE = newEntry(newM, E->Value, i);  // Create a new Entry with column number being the original row number
            if(newM->Entries_Row[E->Column] == NULL){
                newM->Entries_Row[E->Column] = newList();
            }
            append(newM->Entries_Row[E->Column], newE);
        }
    }
    return newM;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix newM = newMatrix(A->Size);
    for (int i = 0; i <= A->Size; i++) {
        List L = A->Entries_Row[i];
        if(L != NULL) {
            for (moveFront(L); index(L) >= 0; moveNext(L)) {
                Entry E = get(L);
                Entry newE = newEntry(newM, E->Value * x, E->Column);  // Create a new Entry with value being x times the original value
                if(newM->Entries_Row[i] == NULL){
                    newM->Entries_Row[i] = newList();
                }
                append(newM->Entries_Row[i], newE);
            }
        }
    }
    if (x == 0) newM->NNZ = 0;
    else newM->NNZ = A->NNZ;
    return newM;
}

Matrix sum(Matrix A, Matrix B) {
    if (A->Size != B->Size) {
        printf("Matrix Error: calling sum() on different size Matrices\n");
        exit(1);
    }

    if(equals(A, B) == 1) return scalarMult(2, A);

    Matrix newM = newMatrix(A->Size);
    for (int i = 1; i <= A->Size; i++) {
        List listA = A->Entries_Row[i];
        List listB = B->Entries_Row[i];
        List listNew = newM->Entries_Row[i];

        moveFront(listA);
        moveFront(listB);

        while (index(listA) >= 0 && index(listB) >= 0) {
            Entry entryA = get(listA);
            Entry entryB = get(listB);

            if (entryA->Column > entryB->Column) {
                append(listNew, newEntry(newM, entryB->Value, entryB->Column));
                (newM->NNZ)++;
                moveNext(listB);
            } else if (entryA->Column < entryB->Column) {
                append(listNew, newEntry(newM, entryA->Value, entryA->Column));
                (newM->NNZ)++;
                moveNext(listA);
            } else {
                double value = entryA->Value + entryB->Value;
                if(value != 0) {
                    append(listNew, newEntry(newM, value, entryA->Column));
                    (newM->NNZ)++;
                }
                moveNext(listA);
                moveNext(listB);
            }
        }

        // Process remaining entries in each list
        while (index(listA) >= 0) {
            Entry entryA = get(listA);
            append(listNew, newEntry(newM, entryA->Value, entryA->Column));
            (newM->NNZ)++;
            moveNext(listA);
        }

        while (index(listB) >= 0) {
            Entry entryB = get(listB);
            append(listNew, newEntry(newM, entryB->Value, entryB->Column));
            (newM->NNZ)++;
            moveNext(listB);
        }
    }
    return newM;
}

Matrix diff(Matrix A, Matrix B) {
    if (A->Size != B->Size) {
        printf("Matrix Error: calling diff() on different size Matrices\n");
        exit(1);
    }

    Matrix newM = newMatrix(A->Size);
    for (int i = 0; i <= A->Size; i++) {
        List listA = A->Entries_Row[i];
        List listB = B->Entries_Row[i];
        List listNew = newM->Entries_Row[i];

        moveFront(listA);
        moveFront(listB);

        while (index(listA) >= 0 && index(listB) >= 0) {
            Entry entryA = get(listA);
            Entry entryB = get(listB);

            if (entryA->Column > entryB->Column) {
                if (entryB->Value != 0) {
                    append(listNew, newEntry(newM, -entryB->Value, entryB->Column));
                    newM->NNZ++;
                }
                moveNext(listB);
            } else if (entryA->Column < entryB->Column) {
                if (entryA->Value != 0) {
                    append(listNew, newEntry(newM, entryA->Value, entryA->Column));
                    newM->NNZ++;
                }
                moveNext(listA);
            } else { // entryA->Column == entryB->Column
                double value = entryA->Value - entryB->Value;
                if (value != 0) {
                    append(listNew, newEntry(newM, value, entryA->Column));
                    newM->NNZ++;
                }
                moveNext(listA);
                moveNext(listB);
            }
        }

        // Process remaining entries in each list
        while (index(listA) >= 0) {
            Entry entryA = get(listA);
            if (entryA->Value != 0) {
                append(listNew, newEntry(newM, entryA->Value, entryA->Column));
                newM->NNZ++;
            }
            moveNext(listA);
        }

        while (index(listB) >= 0) {
            Entry entryB = get(listB);
            if (entryB->Value != 0) {
                append(listNew, newEntry(newM, -entryB->Value, entryB->Column));
                newM->NNZ++;
            }
            moveNext(listB);
        }
    }
    return newM;
}

double vectorDot(List P, List Q) {
    moveFront(P);
    moveFront(Q);
    double dotProduct = 0.0;

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry entryP = get(P);
        Entry entryQ = get(Q);

        if (entryP->Column < entryQ->Column) {
            moveNext(P);
        } else if (entryQ->Column < entryP->Column) {
            moveNext(Q);
        } else {
            dotProduct += entryP->Value * entryQ->Value;
            moveNext(P);
            moveNext(Q);
        }
    }

    return dotProduct;
}

Matrix product(Matrix A, Matrix B) {
    if(A->NNZ == 0 || B->NNZ == 0)
        return newMatrix(A->Size); // return an empty matrix if A or B is empty

    if (A->Size != B->Size) {
        fprintf(stderr, "Matrix product: Matrices should be of the same size.\n");
        exit(1);
    }

    Matrix transposeB = transpose(B); // Transposed version of B

    Matrix AB = newMatrix(A->Size);

    for(int i=1; i<=A->Size; i++) {
        List rowA = A->Entries_Row[i];
        if(rowA->Length == 0) continue; // skip if rowA is zero

        for(int j=1; j<=A->Size; j++) {
            List colB = transposeB->Entries_Row[j];
            if(colB->Length == 0) continue; // skip if columnB is zero

            double value = vectorDot(rowA, colB);
            if(value != 0.0) {
                append(AB->Entries_Row[i], newEntry(AB, value, j));
                (AB->NNZ)++;
            }
        }
    }

    freeMatrix(&transposeB); // Free the transposed matrix when done.

    return AB;
}

void printMatrix(FILE* out, Matrix M) {
    if (out == NULL || M == NULL) {
        printf("printMatrix() out or M is NULL\n");
        exit(EXIT_FAILURE);;
    }
    for (int i = 1; i <= size(M); i++) {
        if (length(M->Entries_Row[i]) > 0) {
            fprintf(out, "%d: ", i);
            moveFront(M->Entries_Row[i]);
            while(index(M->Entries_Row[i]) >= 0) {
                Entry e = get(M->Entries_Row[i]);
                fprintf(out, "(%d, %.1f) ", e->Column, e->Value);
                moveNext(M->Entries_Row[i]);
            }
            fprintf(out, "\n");
        }
    }
}


/*
int main() {
    Matrix A = newMatrix(10);
    Matrix B = newMatrix(10);

    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 3, 1);

    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);


    for(int i = 1; i <= A->Size; i++) {
        moveFront(A->Entries_Row[i]);
        for(; index(A->Entries_Row[i]) >= 0; ) {
            //if((A->Entries_Row[i])->Cursor == NULL) continue;
            printf("R%dC%d, V%f;   ", i, ((Entry) get(A->Entries_Row[i]))->Column, ((Entry) get(A->Entries_Row[i]))->Value);
            //moveNext(A->Entries_Row[i]);
            //(((Entry) get(A->Entries_Row[i]))->Column == length(A->Entries_Row[i])) ? printf("\n") : (void)0;
            moveNext(A->Entries_Row[i]);
            (index(A->Entries_Row[i]) < 0) ? printf("\n") : (void)0;
        }
        //printf("\n");
    }

    printf("A's NNZ %d\n", A->NNZ);


    for(int j = 1; j <= B->Size; j++) {
        moveFront(B->Entries_Row[j]);
        for(; index(B->Entries_Row[j]) >= 0; ) {
            //if((A->Entries_Row[i])->Cursor == NULL) continue;
            printf("R%dC%d, V%f;   ", j, ((Entry) get(B->Entries_Row[j]))->Column, ((Entry) get(B->Entries_Row[j]))->Value);
            //moveNext(A->Entries_Row[i]);
            //(((Entry) get(A->Entries_Row[i]))->Column == length(A->Entries_Row[i])) ? printf("\n") : (void)0;
            moveNext(B->Entries_Row[j]);
            (index(B->Entries_Row[j]) < 0) ? printf("\n") : (void)0;
        }
        //printf("\n");
    }
    printf("B's NNZ %d\n", B->NNZ);
    fflush(stdout);


    if (!equals(A, B))
        printf("no EQ");

    //fflush(stdout);


    freeMatrix(&A);
    freeMatrix(&B);
    return 0;
}
 */


/*

void printMatrix(FILE* out, Matrix M) {
    if(M == NULL) {
        fprintf(stderr, "printMatrix M is NULL!");
        exit(1);
    }
    for(int i = 1; i <= M->Size; i++) {
        if(length(M->Entries_Row[i]) < 1) continue;
        fprintf(out, "%d: ", i);
        moveFront(M->Entries_Row[i]);
        while(index(M->Entries_Row[i]) >= 0) {
            Entry E = get(M->Entries_Row[i]);
            fprintf(out, "(%d, %.1f) ", E->Column, );
        }
    }
}

int main() {
    // Create a new 3x3 Matrix.
    Matrix M = newMatrix(3);

    // Populating with some initial values.
    append(M->Entries_Row[1], newEntry(M, 1.0, 1)); // Matrix M:
    append(M->Entries_Row[2], newEntry(M, 2.0, 2)); // 1 0 0
    append(M->Entries_Row[3], newEntry(M, 3.0, 3)); // 0 2 0
    // 0 0 3

    // Print the initial Matrix.
    printf("Initial Matrix:\n");
    for(int i = 1; i <= M->Size; i++) {
        printMatrixRow(M->Entries_Row[i]);
    }

    //freeMatrix(&M);


    // Create a copy of the original matrix M.
    Matrix N = copy(M);
    //freeMatrix(&M);
    //freeMatrix(&N);


    printf("\nMatrix copy before changing entries:\n");
    for(int i = 1; i <= N->Size; i++) {
        printMatrixRow(N->Entries_Row[i]);
    }
    //freeMatrix(&M);
    //freeMatrix(&N);


    // Change some entries in the copy.
    changeEntry(N, 1, 1, 10.0);
    changeEntry(N, 2, 2, 20.0);
    changeEntry(N, 3, 3, 30.0);




    // Print the Matrix copy after changing entries.
    printf("\nMatrix copy after changing entries:\n");
    for(int i = 1; i <= N->Size; i++) {
        printMatrixRow(N->Entries_Row[i]);
    }

    printf("\nMatrix original:\n");
    for(int i = 1; i <= M->Size; i++) {
        printMatrixRow(M->Entries_Row[i]);
    }

    // Free the Matrices when done.
    //makeZero(M);
    //makeZero(N);
    freeMatrix(&M);
    freeMatrix(&N);

    // Create a new 3x3 Matrix.
    M = newMatrix(3);

    // Populating with some initial values.
    append(M->Entries_Row[1], newEntry(M, 1.0, 1)); // Matrix M:
    append(M->Entries_Row[1], newEntry(M, 5.0, 2));
    append(M->Entries_Row[1], newEntry(M, 7.0, 3));
    append(M->Entries_Row[2], newEntry(M, 2.0, 1)); // 1 5 7
    append(M->Entries_Row[2], newEntry(M, 5.0, 2));
    append(M->Entries_Row[2], newEntry(M, 8.0, 3));
    append(M->Entries_Row[3], newEntry(M, 3.0, 1)); // 2 5 8
    append(M->Entries_Row[3], newEntry(M, 6.0, 2));
    append(M->Entries_Row[3], newEntry(M, 9.0, 3));
                                                                        // 3 6 9

    // Print the initial Matrix.
    printf("TRANSPOSE TEST Initial Matrix:\n");
    for(int i = 1; i <= M->Size; i++) {
        printMatrixRow(M->Entries_Row[i]);
    }

    // Transpose the matrix M.
    Matrix T = transpose(M);

    printf("\nTransposed Matrix:\n");
    for(int i = 1; i <= T->Size; i++) {
        printMatrixRow(T->Entries_Row[i]);
    }

    // Free the Matrices when done.
    freeMatrix(&M);
    freeMatrix(&T);



    Matrix S = newMatrix(3);
    append(S->Entries_Row[1], newEntry(S, 1.0, 1)); // Matrix S:
    append(S->Entries_Row[2], newEntry(S, 2.0, 2)); // 1 0 0
    append(S->Entries_Row[3], newEntry(S, 3.0, 3)); // 0 2 0
    // 0 0 3

    // Print the initial Matrix.
    printf("Initial Matrix for Scalar Multiplication:\n");
    for(int i = 1; i <= S->Size; i++) {
        printMatrixRow(S->Entries_Row[i]);
    }

    // Conduct scalar multiplication
    double scalar = 2.0;
    Matrix SM = scalarMult(scalar, S);

    // Print the resulting Matrix.
    printf("\nResult of Scalar Multiplication:\n");
    for(int i = 1; i <= SM->Size; i++) {
        printMatrixRow(SM->Entries_Row[i]);
    }

    // Free S and SM when done.
    freeMatrix(&S);
    freeMatrix(&SM);

    // Create two new 3x3 Matrices.
    Matrix Q = newMatrix(3);
    Matrix R = newMatrix(3);

    // Populating with some initial values.
    append(Q->Entries_Row[1], newEntry(Q, 1.0, 1)); // Matrix Q:
    append(Q->Entries_Row[2], newEntry(Q, 2.0, 2)); // 1 0 0
    append(Q->Entries_Row[3], newEntry(Q, 3.0, 3)); // 0 2 0
    // 0 0 3
    append(R->Entries_Row[1], newEntry(R, 4.0, 1)); // Matrix R:
    append(R->Entries_Row[2], newEntry(R, 5.0, 2)); // 4 0 0
    append(R->Entries_Row[3], newEntry(R, 6.0, 3)); // 0 5 0
    // 0 0 6

    // Print the initial Matrices.
    printf("Initial Matrix Q:\n");
    for(int i = 1; i <= Q->Size; i++) {
        printMatrixRow(Q->Entries_Row[i]);
    }

    printf("\nInitial Matrix R:\n");
    for(int i = 1; i <= R->Size; i++) {
        printMatrixRow(R->Entries_Row[i]);
    }

    // Add the matrices
    Matrix SR = sum(Q, R);

    // Print the resulting Matrix.
    printf("\nResult of Sum:\n");
    for (int i = 1; i <= SR->Size; i++) {
        printMatrixRow(SR->Entries_Row[i]);
    }

    printf("\nNon-Zero Entries in the Sum: %d\n", SR->NNZ);

    // Subtract the matrices
    Matrix DR = diff(Q, R);

    // Print the resulting Matrix.
    printf("\nResult of Difference:\n");
    for (int i = 1; i <= DR->Size; i++) {
        printMatrixRow(DR->Entries_Row[i]);
    }

    printf("\nNon-Zero Entries in the Difference: %d\n", DR->NNZ);

    // Free Q, R, SR, and DR when done.
    freeMatrix(&Q);
    freeMatrix(&R);
    freeMatrix(&SR);
    freeMatrix(&DR);


    // Create two new 3x3 matrices for testing the product function.
    Matrix A = newMatrix(3);
    append(A->Entries_Row[1], newEntry(A, 1.0, 1)); // Matrix A:
    append(A->Entries_Row[1], newEntry(A, 2.0, 2)); // 1 2 0
    append(A->Entries_Row[2], newEntry(A, 3.0, 1)); // 3 0 0
    // 0 0 0
    A->NNZ = 3;

    Matrix B = newMatrix(3);
    append(B->Entries_Row[1], newEntry(B, 4.0, 1)); // Matrix B:
    append(B->Entries_Row[1], newEntry(B, 5.0, 2)); // 4 5 0
    // 0 0 0
    // 0 0 0
    B->NNZ = 2;

    // Print the initial matrices.
    printf("Initial Matrix A:\n");
    for(int i = 1; i <= A->Size; i++) {
        printMatrixRow(A->Entries_Row[i]);
    }
    printf("\nInitial Matrix B:\n");
    for(int i = 1; i <= B->Size; i++) {
        printMatrixRow(B->Entries_Row[i]);
    }

    // Compute the product of the matrices
    Matrix P = product(A, B);

    // Print the resulting Matrix.
    printf("\nResult of A*B Product:\n");
    for (int i = 1; i <= P->Size; i++) {
        printMatrixRow(P->Entries_Row[i]);
    }

    // Free A, B, P when done.
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&P);

    return 0;
}
 */