/**
 * FindComponents.c
 * CSE 101 PA3
 * Zihua Li, CruzID: zli487
 **/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Invalid number of arguments. Usage: %s input_file output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if(input_file == NULL) {
        fprintf(stderr, "Unable to open the input file.\n");
        exit(EXIT_FAILURE);
    }

    // Open the output file
    FILE *output_file = fopen(argv[2], "w");
    if(output_file == NULL) {
        fprintf(stderr, "Unable to create or write to the output file.\n");
        fclose(input_file); // Close the input file
        exit(EXIT_FAILURE);
    }

    // number of vertices
    int n_v;
    fscanf(input_file, " %d", &n_v);
    //printf("this is n_v: %d \n", n_v);
    //fflush(stdout);
    Graph G = newGraph(n_v); // new graph
    //printf("new graph ok\n");
    //fflush(stdout);

    int a = 0, b = 0;
    while(fscanf(input_file, " %d %d", &a, &b) == 2 && a != 0 && b != 0) {
        addArc(G, a, b);
    }
    //printf("addArc ok\n");
    //fflush(stdout);

    fprintf(output_file, "Adjacency list representation of G:\n");
    printGraph(output_file, G);
    fprintf(output_file, "\n");

    List L = newList();
    for (int i = 1; i < n_v; i++) {
        append(L, i);
    }
    DFS(G, L);

    Graph G_transpose = transpose(G);
    DFS(G_transpose, L);

    int n_strongly = 0;
    for(int i = 1; i <= n_v; i++) {
        (getParent(G_transpose, i) == NIL) ? n_strongly++ : (void)0;
    }
    List* L_strongly = malloc(n_strongly * sizeof(List));

    for(int i = 0; i < n_strongly; i++) {
        L_strongly[i] = newList();
    }
    moveBack(L);

    for(int i = 0, j = 0; index(L) != -1; movePrev(L)) {
        j = get(L);
        prepend(L_strongly[i], j);
        (getParent(G_transpose, j) == NIL) ? i++ : (void)0;
    }

    fprintf(output_file, "G contains %d strongly connected components:\n", n_strongly);

    for(int i = 0; i < n_strongly; i++) {
        fprintf(output_file, "Component %d: ", (i + 1));
        printList(output_file, L_strongly[i]);
        fprintf(output_file, "\n");
    }

    // free all memory
    for(int i = 0; i < n_strongly; i++) {
        freeList(&L_strongly[i]);
    }
    free(L_strongly);
    freeList(&L);
    freeGraph(&G);
    freeGraph(&G_transpose);
    fclose(input_file);
    fclose(output_file);

    return 0;
}