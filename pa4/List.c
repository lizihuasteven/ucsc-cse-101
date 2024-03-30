/**
 * List.c
 * CSE 101 PA4
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
    L->index = -1;
    return L;
}

Node newNode(void* Data) {
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
    return L->index;
}

void* front(List L) {
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

void* back(List L) {
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

void* get(List L) {
    if(L == NULL || L->Cursor == NULL) {
        fprintf(stderr, "get(List L) List does not exist.");
        exit(1);
    } else {
        if(length(L) > 0) {
            if(index(L) >= 0) {
                return L->Cursor->Data;
            } else {
                fprintf(stderr, "index is smaller than 0.");
                exit(1);
            }
        } else {
            fprintf(stderr, "Length is not greater than 0.");
            exit(1);
        }
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
    L->index = -1;
}

void set(List L, void* x) {
    if(L == NULL) {
        fprintf(stderr, "List does not exist.");
        exit(1);
    }
    L->Cursor->Data = x;
}

void moveFront(List L) {
    if(L->Length > 0) {
        L->index = 0;
        L->Cursor = L->Front;
    }
}

void moveBack(List L) {
    if(L->Length > 0) {
        L->index = L->Length - 1;
        L->Cursor = L->Back;
    }
}

void movePrev(List L) {
    if(L->Cursor != NULL && L->Cursor != L->Front) {
        L->index = L->index - 1;
        L->Cursor = L->Cursor->Prev;
    } else {
        if(L->Cursor == L->Front) {
            L->Cursor = NULL;
            L->index = -1;
        }
    }
}

void moveNext(List L) {
    if(L->Cursor != NULL && L->Cursor != L->Back) {
        L->index = L->index + 1;
        L->Cursor = L->Cursor->Next;
    } else {
        if(L->Cursor == L->Back) {
            L->Cursor = NULL;
            L->index = -1;
        }
    }
}

void prepend(List L, void* x) {
    Node N = newNode(x);
    if (L->Length > 0) {
        N->Next = L->Front;
        L->Front->Prev = N;
        L->Front = N;
        if (L->Cursor != NULL) {
            L->index++;
        }
    } else {
        L->Front = N;
        L->Back = N;
    }
    L->Length++;
}

void append(List L, void* x) {
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
        L->index = 0;
    } L->Length = L->Length + 1;
}

void insertBefore(List L, void* x) {
    if(L->Cursor == L->Front) {
        Node N = newNode(x);
        N->Next = L->Cursor;
        L->Cursor->Prev = N;
        L->Front = N;
        L->index = L->index + 1;
    } else {
        Node N = newNode(x);
        N->Next = L->Cursor;
        N->Prev = L->Cursor->Prev;
        L->Cursor->Prev->Next = N;
        L->Cursor->Prev = N;
        L->index = L->index + 1;
    } L->Length = L->Length + 1;
}

void insertAfter(List L, void* x) {
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
    } else {
        if(L->Cursor == L->Front) {
            Node origFront = L->Front;
            L->Front = L->Front->Next;
            L->Cursor = NULL;
            L->index = -1;
            freeNode(&origFront);
        } else {
            Node origFront = L->Front;
            L->Front = L->Front->Next;
            L->index = L->index - 1;
            freeNode(&origFront);
        }
    } (L->Length != 0) ? L->Length = L->Length - 1 : (void)0;
}

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
        L->index = -1;
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
        L->index = -1;
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

int listindex(List L) {
    return index(L);
}
