/**
 * WordFrequency.cpp
 * CSE 101 PA8
 * Zihua Li, CruzID: zli487
 **/

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <algorithm>
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
    std::string S_line, S_key, delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary D;
    uint64_t len, start, end;
    while(getline(input_file, S_line)) {
        len = S_line.length();
        start = std::min(S_line.find_first_not_of(delim), len);
        end = std::min(S_line.find_first_of(delim, start), len);
        S_key = S_line.substr(start, (end - start));
        while(!S_key.empty()) {
            uint64_t i = 0;
            while (i < S_key.length()) {
                S_key[i] = tolower(S_key[i]);
                i++;
            }
            if (D.contains(S_key)) D.getValue(S_key)++;
            else D.setValue(S_key, 1);
            start = std::min(S_line.find_first_not_of(delim, (end + 1)), len);
            end = std::min(S_line.find_first_of(delim, start), len);
            S_key = S_line.substr(start, (end - start));
        }
    } output_file << D << std::endl;
    input_file.close();
    output_file.close();
    return 0;
}