#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    int n = 5; // Number of vertices in the graph
    Graph G = newGraph(n);

    // Add edges
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 1);

    // Print the graph
    printf("Graph after adding edges:\n");
    printGraph(stdout, G);

    // Check size and order
    printf("Order of G: %d\n", getOrder(G));
    printf("Size of G: %d\n", getSize(G));

    // Run BFS from vertex 1
    BFS(G, 1);

    // Test getPath
    List L = newList();
    getPath(L, G, 3); // Get path from 1 to 3
    printf("Path from 1 to 3: ");
    printList(stdout, L);
    printf("\n");

    // Test other access functions
    printf("Parent of 3: %d\n", getParent(G, 3));
    printf("Distance from 1 to 3: %d\n", getDist(G, 3));

    // Free objects
    freeList(&L);
    freeGraph(&G);

    return 0;
}
