#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// Private GraphObj type
typedef struct GraphObj {
    List* neighbors; // Array of Lists for adjacency information
    int* color;      // Array of colors (white, gray, black)
    int* parent;     // Array of parent vertices
    int* distance;   // Array of distances
    int order;       // Number of vertices
    int size;        // Number of edges
    int source;      // Label of the most recent source vertex
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->neighbors = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->distance = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getSource(Graph G) {
    return G->source;
}

/*** More Access functions ***/
int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDist(Graph G, int u) {
    return G->distance[u];
}

void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) return;
    if (u == getSource(G)) append(L, getSource(G));
    else if (G->parent[u] == NIL) append(L, NIL);
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->neighbors[i]);
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if(u == v) return;

    List TempList = G->neighbors[u];
    for(moveFront(TempList); index(TempList) != -1 && get(TempList) < v; ) {
        moveNext(TempList);
    }
    if (index(TempList) == -1) append(TempList, v);
    else insertBefore(TempList, v);
    //freeList(&TempList);

    List TempList2 = G->neighbors[v];
    for(moveFront(TempList2); index(TempList2) != -1 && get(TempList2) < u; ) {
        moveNext(TempList2);
    }
    if (index(TempList2) == -1) append(TempList2, u);
    else insertBefore(TempList2, u);
    //freeList(&TempList2);

    (G->size)++;
}

void addArc(Graph G, int u, int v) {
    if(u==v) return;
    append(G->neighbors[u], v);
    (G->size)++;
}

void BFS(Graph G, int s) {
    G->source = s;
    for (int i = 1; i <= G->order; i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    // Create a new list to use as a queue
    List Q = newList();
    append(Q, s);

    while (length(Q) > 0) {
        int x = front(Q);
        deleteFront(Q);
        List Temp = G->neighbors[x];
        for (moveFront(Temp); index(Temp) >= 0; moveNext(Temp)) {
            int y = get(Temp);
            if (G->color[y] == WHITE) {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
        }
        G->color[x] = BLACK;
        //freeList(&Temp);
    }
    freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
    int printed;
    for (int i = 1; i <= getOrder(G); i++) {
        printed = 0;
        fprintf(out, "%d:", i);
        moveFront(G->neighbors[i]);
        while(index(G->neighbors[i]) >= 0){
            fprintf(out, " %d", get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
            printed = 1;
        }
        (printed == 0) ? fprintf(out, " ") : (void)0;
        fprintf(out, "\n");
    }
}
