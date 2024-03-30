/**
 * List.h
 * CSE 101 PA3
 * Zihua Li, CruzID: zli487
 **/

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct NodeObj* Node;
typedef struct ListObj* List;

typedef struct NodeObj {
    int Data;
    struct NodeObj* Prev;
    struct NodeObj* Next;
} NodeObj;

typedef struct ListObj {
    Node Front;
    Node Back;
    Node Cursor;
    int Length;
    int Index;
} ListObj;

// Constructors-Destructors
List newList(void);
void freeList(List* pL);
void freeNode(Node* pN);

// Access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

// Manipulation procedures
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations
void printList(FILE* out, List L);
List copyList(List L);

int listIndex(List L);

#endif
