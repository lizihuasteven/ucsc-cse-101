/**
 * Sparse.c
 * CSE 101 PA4
 * Zihua Li, CruzID: zli487
 **/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments. Usage: %s input_file output_file\n", argv[0]);
        exit(1);
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "Unable to open the input file.\n");
        exit(1);
    }

    // Open the output file
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "Unable to create or write to the output file.\n");
        fclose(input_file); // Close the input file
        exit(1);
    }

    // n is dimension, a is A_NNZ, b is B_NNZ
    int n = 0, a = 0, b = 0;
    fscanf(input_file, "%d %d %d", &n, &a, &b);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    for (int i = 1; i <= a; i++) {
        double Value;
        int Row, Column;
        fscanf(input_file, "%d %d %lf", &Row, &Column, &Value);
        changeEntry(A, Row, Column, Value);
    }
    for (int i = 1; i <= b; i++) {
        double Value;
        int Row, Column;
        fscanf(input_file, "%d %d %lf", &Row, &Column, &Value);
        changeEntry(B, Row, Column, Value);
    }

    // Start output

    fprintf(output_file, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output_file, A);

    fprintf(output_file, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(output_file, B);
    fprintf(output_file, "\n");

    // (1.5)*A =
    fprintf(output_file, "(1.5)*A =\n");
    Matrix Ax1_5 = scalarMult(1.5, A);
    printMatrix(output_file, Ax1_5);
    fprintf(output_file, "\n");
    freeMatrix(&Ax1_5);

    // A+B =
    fprintf(output_file, "A+B =\n");
    Matrix AB_sum = sum(A, B);
    printMatrix(output_file, AB_sum);
    fprintf(output_file, "\n");
    freeMatrix(&AB_sum);

    // A+A =
    fprintf(output_file, "A+A =\n");
    Matrix AA_sum = sum(A, A);
    printMatrix(output_file, AA_sum);
    fprintf(output_file, "\n");
    freeMatrix(&AA_sum);

    // B-A =
    fprintf(output_file, "B-A =\n");
    Matrix BA_diff = diff(B, A);
    printMatrix(output_file, BA_diff);
    fprintf(output_file, "\n");
    freeMatrix(&BA_diff);

    // A-A =
    fprintf(output_file, "A-A =\n");
    Matrix AA_diff = diff(A, A);
    printMatrix(output_file, AA_diff);
    fprintf(output_file, "\n");
    freeMatrix(&AA_diff);

    // Transpose(A) =
    fprintf(output_file, "Transpose(A) =\n");
    Matrix A_trans = transpose(A);
    printMatrix(output_file, A_trans);
    fprintf(output_file, "\n");
    freeMatrix(&A_trans);

    // A*B =
    fprintf(output_file, "A*B =\n");
    Matrix AB_product = product(A, B);
    printMatrix(output_file, AB_product);
    fprintf(output_file, "\n");
    freeMatrix(&AB_product);

    // B*B =
    fprintf(output_file, "B*B =\n");
    Matrix BB_product = product(B, B);
    printMatrix(output_file, BB_product);
    fprintf(output_file, "\n");
    freeMatrix(&BB_product);

    // freeing stuff
    freeMatrix(&A);
    freeMatrix(&B);
    fclose(input_file);
    fclose(output_file);
    return 0;
}