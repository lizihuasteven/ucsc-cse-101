//
// Created by Zihua Li on 3/10/24.
//

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "Dictionary.h"

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
    std::ofstream output_file(argv[2]);
    int cnt = 1;
    Dictionary D;
    std::string S;
    while(getline(input_file, S)) {
        D.setValue(S, cnt);
        cnt++;
    }
    output_file << D.to_string() << std::endl;
    output_file << D.pre_string() << std::endl;
    input_file.close();
    output_file.close();
    return 0;
}