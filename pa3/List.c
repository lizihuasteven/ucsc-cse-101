/**
 * List.c
 * CSE 101 PA3
 * Zihua Li, CruzID: zli487
 **/


#include "List.h"
#include <stdlib.h>

// Implementations of the functions

List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->Front = NULL;
    L->Back = NULL;
    L->Cursor = NULL;
    L->Length = 0;
    L->Index = -1;
    return L;
}

Node newNode(int Data) {
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        fprintf(stderr, "Unable to allocate memory for new node.\n");
        exit(EXIT_FAILURE);
    }
    N->Data = Data;
    N->Prev = NULL;
    N->Next = NULL;
    return N;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        //pL = NULL;
        *pL = NULL;
    } else {
        fprintf(stderr, "List does not exist.");
        exit(1);
    }
}

void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    } else {
        fprintf(stderr, "List does not exist.");
        exit(1);
    }
}

int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List does not exist.");
        exit(1); //ERROR_FAILURE
    } else {
        return L->Length;
    }
}

int index(List L) {
    if(L == NULL) {
        return -1;
    }
    return L->Index;
}

int front(List L) {
    if(L == NULL) {
        fprintf(stderr, "List does not exist.");
        exit(1);
    } else {
        if(length(L) > 0) {
            return L->Front->Data;
        } else {
            fprintf(stderr, "Length is not greater than 0.");
            exit(1);
        }
    }
}

int back(List L) {
    if(L == NULL) {
        fprintf(stderr, "List does not exist.");
        exit(1);
    } else {
        if(length(L) > 0) {
            return L->Back->Data;
        } else {
            fprintf(stderr, "Length is not greater than 0.");
            exit(1);
        }
    }
}

int get(List L) {
    if(L == NULL || L->Cursor == NULL) {
        fprintf(stderr, "get(List L) List does not exist.");
        exit(1);
    } else {
        if(length(L) > 0) {
            if(index(L) >= 0) {
                return L->Cursor->Data;
            } else {
                fprintf(stderr, "Index is smaller than 0.");
                exit(1);
            }
        } else {
            fprintf(stderr, "Length is not greater than 0.");
            exit(1);
        }
    }
}

bool equals(List A, List B) {
    if(A->Length == B->Length) {
        Node ANode = A->Front;
        Node BNode = B->Front;
        //moveFront(A);
        //moveFront(B);
        while(ANode != NULL) {
            if(ANode->Data != BNode->Data) {
                return false;
            }
            ANode = ANode->Next;
            BNode = BNode->Next;
        }
        return true;
    } else {
        // what if len(A) and len(B) both equal to 0???
        return false;
    }
}

void clear(List L) {
    if(L == NULL) {
        fprintf(stderr, "List does not exist.");
        exit(1);
    }
    if(L->Length == 0) return;

    Node nodePosition = L->Front;
    while (nodePosition != NULL) {
        Node nextNode = nodePosition->Next;
        freeNode(&nodePosition);
        nodePosition = nextNode;
    }
    L->Front = NULL;
    L->Back = NULL;
    L->Cursor = NULL;
    L->Length = 0;
    L->Index = -1;
}

void set(List L, int x) {
    if(L == NULL) {
        fprintf(stderr, "List does not exist.");
        exit(1);
    }
    L->Cursor->Data = x;
}

void moveFront(List L) {
    if(L->Length > 0) {
        L->Index = 0;
        L->Cursor = L->Front;
    }
}

void moveBack(List L) {
    if(L->Length > 0) {
        L->Index = L->Length - 1;
        L->Cursor = L->Back;
    }
}

void movePrev(List L) {
    if(L->Cursor != NULL && L->Cursor != L->Front) {
        L->Index = L->Index - 1;
        L->Cursor = L->Cursor->Prev;
    } else {
        if(L->Cursor == L->Front) {
            L->Cursor = NULL;
            L->Index = -1;
        }
    }
}

void moveNext(List L) {
    if(L->Cursor != NULL && L->Cursor != L->Back) {
        L->Index = L->Index + 1;
        L->Cursor = L->Cursor->Next;
    } else {
        if(L->Cursor == L->Back) {
            L->Cursor = NULL;
            L->Index = -1;
        }
    }
}

void prepend(List L, int x) {
    Node N = newNode(x);
    if (L->Length > 0) {
        N->Next = L->Front;
        L->Front->Prev = N;
        L->Front = N;
        if (L->Cursor != NULL) {
            L->Index++;
        }
    } else {
        L->Front = N;
        L->Back = N;
    }
    L->Length++;
}

void append(List L, int x) {
    if(L->Length != 0) {
        Node N = newNode(x);
        N->Prev = L->Back;
        L->Back->Next = N;
        L->Back = N;
    } else {
        Node N = newNode(x);
        L->Front = N;
        L->Back = N;
        L->Cursor = N;
        L->Index = 0;
    } L->Length = L->Length + 1;
}

void insertBefore(List L, int x) {
    if(L->Cursor == L->Front) {
        Node N = newNode(x);
        N->Next = L->Cursor;
        L->Cursor->Prev = N;
        L->Front = N;
        L->Index = L->Index + 1;
    } else {
        Node N = newNode(x);
        N->Next = L->Cursor;
        N->Prev = L->Cursor->Prev;
        L->Cursor->Prev->Next = N;
        L->Cursor->Prev = N;
        L->Index = L->Index + 1;
    } L->Length = L->Length + 1;
}

void insertAfter(List L, int x) {
    if(L->Cursor == L->Back) {
        Node N = newNode(x);
        N->Prev = L->Cursor;
        L->Cursor->Next = N;
        L->Back = N;
    } else {
        Node N = newNode(x);
        N->Prev = L->Cursor;
        N->Next = L->Cursor->Next;
        L->Cursor->Next->Prev = N;
        L->Cursor->Next = N;
    } L->Length = L->Length + 1;
}

void deleteFront(List L) {
    if(L->Length < 2) {
        clear(L);
        return;
    } else {
        if(L->Cursor == L->Front) {
            Node origFront = L->Front;
            L->Front = L->Front->Next;
            L->Cursor = NULL;
            L->Index = -1;
            freeNode(&origFront);
        } else {
            Node origFront = L->Front;
            L->Front = L->Front->Next;
            L->Index = L->Index - 1;
            freeNode(&origFront);
        }
    } (L->Length)--;
}

/*
void deleteBack(List L) {
    if(L->Length < 2) {
        clear(L);
    } else {
        if(L->Cursor == L->Back) {
            Node origBack = L->Back;
            L->Back = L->Back->Prev;
            L->Cursor = NULL;
            L->Index = -1;
            freeNode(&origBack);
        } else {
            Node origBack = L->Back;
            L->Back = L->Back->Prev;
            freeNode(&origBack);
        }
    } L->Length = L->Length - 1;
}
*/

void deleteBack(List L) {
    if (L == NULL || L->Length == 0) {
        fprintf(stderr, "DeleteBack: List is empty or does not exist.\n");
        return;
    }

    Node temp = L->Back;
    if (L->Length > 1) {
        L->Back = L->Back->Prev;
        L->Back->Next = NULL;
    } else {
        L->Front = L->Back = NULL;
    }

    if (L->Cursor == temp) {
        L->Cursor = NULL;
        L->Index = -1;
    }

    freeNode(&temp);
    L->Length--;
}

void delete(List L) {
    if (L == NULL || L->Cursor == NULL) {
        fprintf(stderr, "Delete: Cursor is NULL or List does not exist.\n");
        return;
    }

    if (L->Cursor == L->Front) {
        deleteFront(L);
    } else if (L->Cursor == L->Back) {
        deleteBack(L);
    } else {
        Node temp = L->Cursor;
        L->Cursor->Prev->Next = L->Cursor->Next;
        L->Cursor->Next->Prev = L->Cursor->Prev;
        L->Length--;
        freeNode(&temp);

        L->Cursor = NULL;
        L->Index = -1;
    }
}


void printList(FILE* out, List L) {
    if(L == NULL) {
        fprintf(stderr, "Invalid List.");
        exit(1);
    } else {
        Node nodeCopy = L->Front;
        for(; nodeCopy!=NULL; nodeCopy=nodeCopy->Next) {
            (nodeCopy->Next == NULL) ? fprintf(out, "%d", nodeCopy->Data)
                                     : fprintf(out, "%d ", nodeCopy->Data);
        }
    }
}

List copyList(List L) {
    if(L == NULL) {
        fprintf(stderr, "Invalid List.");
        exit(1);
    } else {
        List createdList = newList();
        Node nodeCopy = L->Front;
        for(; nodeCopy!=NULL; nodeCopy=nodeCopy->Next) {
            append(createdList, nodeCopy->Data);
        } return createdList;
    }
}

int listIndex(List L) {
    return index(L);
}
