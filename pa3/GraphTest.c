/**
 * GraphTest.c
 * CSE 101 PA3
 * Zihua Li, CruzID: zli487
 **/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {
    int n = 5; // Number of vertices in the graph
    Graph G = newGraph(n);

    // Add edges
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 1);

    // Print the graph after adding edges
    printf("Graph after adding edges:\n");
    printGraph(stdout, G);

    // Check size and order
    printf("Order of G: %d\n", getOrder(G));
    printf("Size of G: %d\n", getSize(G));

    // Prepare for DFS - assuming List type and its functions are defined
    List S = newList();
    for (int i = 1; i <= n; i++) {
        append(S, i);
    }

    // Run DFS
    DFS(G, S);

    // Test getDiscover and getFinish
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: discovered at %d, finished at %d\n", i, getDiscover(G, i), getFinish(G, i));
    }

    // Test getPath - this part needs to be adapted as getPath doesn't apply directly like in BFS
    // Assuming getPath is meant to work in the context of DFS paths
    List L = newList();
    printf("Attempting to retrieve a path in DFS context may not directly apply as in BFS.\n");

    // Test other access functions
    printf("Parent of 3: %d\n", getParent(G, 3));

    // Since DFS does not calculate distances in the same way BFS does, distance might not be relevant
    // printf("Distance from 1 to 3: %d\n", getDist(G, 3)); // Not applicable for DFS in the same way as BFS

    // Test transpose and copyGraph
    Graph T = transpose(G);
    Graph C = copyGraph(G);

    printf("Transpose of G:\n");
    printGraph(stdout, T);

    printf("Copy of G:\n");
    printGraph(stdout, C);

    // Make sure to test makeNull
    makeNull(G);
    printf("Graph after calling makeNull:\n");
    printGraph(stdout, G); // Should print an empty graph

    // Free objects
    freeList(&L);
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);

    return 0;
}

