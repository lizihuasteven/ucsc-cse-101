/**
 * Arithmetic.cpp
 * CSE 101 PA6
 * Zihua Li, CruzID: zli487
 **/

#include "List.h"
#include "BigInteger.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments. Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    std::ifstream input_file(argv[1]); // Open the input file
    if (!input_file) {
        fprintf(stderr, "Unable to open the input file.\n");
        exit(1);
    }
    std::ofstream output_file(argv[2]); // Open the output file
    std::string S_A, S_B;
    input_file >> S_A >> S_B;
    BigInteger BI_A = BigInteger(S_A), BI_B = BigInteger(S_B);
    BigInteger BI_const_2 = BigInteger(2), BI_const_3 = BigInteger(3), BI_const_9 = BigInteger(9), BI_const_16 = BigInteger(16);
    // start output
    output_file << BI_A << std::endl << std::endl;
    output_file << BI_B << std::endl << std::endl;
    output_file << BI_A + BI_B << std::endl << std::endl;
    output_file << BI_A - BI_B << std::endl << std::endl;
    output_file << BI_A - BI_A << std::endl << std::endl;
    output_file << (BI_const_3 * BI_A) - (BI_const_2 * BI_B) << std::endl << std::endl;
    output_file << BI_A * BI_B << std::endl << std::endl;
    output_file << BI_A * BI_A << std::endl << std::endl;
    output_file << BI_B * BI_B << std::endl << std::endl;
    output_file << (BI_const_9 * (BI_A * BI_A * BI_A * BI_A)) + (BI_const_16 * (BI_B * BI_B * BI_B * BI_B * BI_B)) << std::endl << std::endl;
    input_file.close();
    output_file.close();
    return 0;
}