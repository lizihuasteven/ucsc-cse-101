/**
 * Shuffle.cpp
 * CSE 101 PA5
 * Zihua Li, CruzID: zli487
 **/

#include "List.h"
#include <cstdio>
#include <cstdlib>

void shuffle(List& D) {
    D.moveFront();
    List L, M;
    while(D.position() < D.length() / 2) L.insertBefore(D.moveNext());
    while(D.position() < D.length()) M.insertBefore(D.moveNext());
    L.moveFront();
    M.moveFront();
    D.clear();
    while(L.position() < L.length() && M.position() < M.length()) {
        D.insertBefore(M.moveNext());
        D.insertBefore(L.moveNext());
    }
    while(L.position() < L.length()) D.insertBefore(L.moveNext());
    while(M.position() < M.length()) D.insertBefore(M.moveNext());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments. Usage: %s deck_size\n", argv[0]);
        exit(1);
    }

    fprintf(stdout, "deck size       shuffle count\n");
    fprintf(stdout, "------------------------------\n");
    List L, L_copy;
    for(int i = 1, count = 0; i <= std::stoi(argv[1]); count = 0, i++) {
        L.moveBack();
        L.insertBefore(i-1);
        L_copy = L;
        shuffle(L);
        count += 1;
        while(true) {
            if (L_copy == L) break;
            shuffle(L);
            count += 1;
        }
        fprintf(stdout, " %-16d%d\n", i, count);
    }
    return 0;
}