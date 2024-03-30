/**
 * List.h
 * CSE 101 PA4
 * Zihua Li, CruzID: zli487
 **/

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct NodeObj* Node;
typedef struct ListObj* List;

typedef struct NodeObj {
    void* Data;
    struct NodeObj* Prev;
    struct NodeObj* Next;
} NodeObj;

typedef struct ListObj {
    Node Front;
    Node Back;
    Node Cursor;
    int Length;
    int index;
} ListObj;

// Constructors-Destructors
List newList(void);
void freeList(List* pL);
void freeNode(Node* pN);

// Access functions
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

// Manipulation procedures
void clear(List L);
void set(List L, void* x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* x);
void append(List L, void* x);
void insertBefore(List L, void* x);
void insertAfter(List L, void* x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations
//void printList(FILE* out, List L);
List copyList(List L);

int listindex(List L);

#endif
