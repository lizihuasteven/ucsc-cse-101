/**
 * Graph.c
 * CSE 101 PA3
 * Zihua Li, CruzID: zli487
 **/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// Private GraphObj type
typedef struct GraphObj {
    List* neighbors; // Array of Lists for adjacency information
    int* color;      // Array of colors (white, gray, black)
    int* parent;     // Array of parent vertices
    int* distance;   // Array of distances
    int* discover;
    int* finish;
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
    G->discover = malloc((n+1) * sizeof(int));
    G->finish = malloc((n+1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
        G->discover[i]= UNDEF;
        G->finish[i] = UNDEF;
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
        free((*pG)->discover);
        free((*pG)->finish);
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
    if (G == NULL) {
        fprintf(stderr, "G is null");
        exit(1);
    }
    if (u >= 1 && u <= getOrder(G)) return G->parent[u];
    else {
        fprintf(stderr, "Invalid Vertex");
        exit(1);
    }
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

int getFinish(Graph G, int u) {
    if (u >= 1 && u <= getOrder(G)) return G->finish[u];
    else {
        fprintf(stderr, "Invalid Vertex");
        exit(1);
    }
}

int getDiscover(Graph G, int u) {
    if (u >= 1 && u <= getOrder(G)) return G->discover[u];
    else {
        fprintf(stderr, "Invalid Vertex");
        exit(1);
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
    addArc(G, u, v);
    addArc(G, v, u);
    (G->size)--;
}

void addArc(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "addArc says Invalid vertex");
        exit(1);
    }
    List L = G->neighbors[u];
    if (length(L) <= 0) append(L, v);
    else {
        moveFront(L);
        while(index(L) >= 0) {
            if (v < get(L)) {
                insertBefore(L, v);
                break;
            }
            if(v == get(L)) return;
            moveNext(L);
        }
        (index(L) < 0) ? append(L, v) : (void)0;
    }
    (G->size)++;
}

void DFS(Graph G, List s) {
    for(int i = 0; i <= getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;
    List L = copyList(s);
    clear(s);
    for(moveFront(L); index(L) >= 0; moveNext(L)) {
        (G->color[get(L)] == WHITE) ? visit(G, s, get(L), &time) : (void)0;
    }
    freeList(&L);
}

void visit(Graph G, List s, int x, int* time) {
    G->discover[x] = ++(*time);
    G->color[x] = GRAY;
    List L = G->neighbors[x];
    for(moveFront(L); index(L) >= 0; moveNext(L)) {
        if(G->color[get(L)] == WHITE) {
            G->parent[get(L)] = x;
            visit(G, s, get(L), time);
        }
    }
    G->color[x] = BLACK;
    G->finish[x] = ++(*time);
    prepend(s, x);
}

Graph transpose(Graph G) {
    Graph returnGraph = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++) {
        List TempList = G->neighbors[i];
        moveFront(TempList);
        for(; index(TempList) != -1; moveNext(TempList)) {
            addArc(returnGraph, get(TempList), i);
        }
    }
    return returnGraph;
}

Graph copyGraph(Graph G) {
    Graph returnGraph1 = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++) {
        List TempList = G->neighbors[i];
        moveFront(TempList);
        for(; index(TempList) != -1; moveNext(TempList)) {
            addArc(returnGraph1, i, get(TempList));
        }
    }
    return returnGraph1;
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
