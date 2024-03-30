#include<stdio.h>
#include<stdlib.h>
#define index __no_index__  // Temporarily rename the index function from strings.h
#include <string.h>
#undef index
#include"Graph.h"

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

    size_t size;
    fscanf(input_file, "%zd", &size);
    Graph G = newGraph(size);

    int Source = 1, Distance = 1;
    /*
    for(Source = 1, Distance = 1; Source != 0 && Distance != 0; addEdge(G, Source, Distance)) {
        fscanf(input_file, "%d %d", &Source, &Distance);
    }
     */

    while(Source != 0 && Distance != 0) {
        fscanf(input_file, "%d %d", &Source, &Distance);
        addEdge(G, Source, Distance);
    }

    printGraph(output_file, G);

    for(fscanf(input_file, "%d %d", &Source, &Distance); Source != 0 || Distance != 0; fscanf(input_file, "%d %d", &Source, &Distance)) {
        BFS(G, Source);
        if(getDist(G, Distance) == INF) {
            fprintf(output_file, "\nThe distance from %d to %d is infinity\n", Source, Distance);
            fprintf(output_file, "No %d-%d path exists\n", Source, Distance);
        } else {
            fprintf(output_file, "\nThe distance from %d to %d is %d\n", Source, Distance, getDist(G, Distance));
            fprintf(output_file, "A shortest %d-%d path is: ", Source, Distance);
            List L = newList();
            getPath(L, G, Distance);
            printList(output_file, L);
            fprintf(output_file, "\n");
            freeList(&L);
        }
    }

    fclose(input_file);
    fclose(output_file);
    freeGraph(&G);

    return 0;
}