/**
 * ListTest.c
 * CSE 101 PA4
 * Zihua Li, CruzID: zli487
 **/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj {
    double Value;
    int Column;
} EntryObj;

void printList(List L) {
    moveFront(L);
    printf("List: ");
    while(index(L) >= 0) {
        Entry entry = (Entry)get(L);
        printf("Column: %d Value: %.2f || ", entry->Column, entry->Value);
        moveNext(L);
    }
    printf("\n");
}

Entry newEntry(int Column, double Value) {
    Entry e = malloc(sizeof(EntryObj));
    e->Column = Column;
    e->Value = Value;
    return e;
}

int main() {
    // Test newList
    List L = newList();

    Entry entries[5];
    for(int i = 0; i < 5; i++) {
        entries[i] = newEntry(i, i*2.5);
        append(L, entries[i]);
    }
    printList(L);

    moveFront(L);
    printList(L);

    moveBack(L);
    printList(L);

    Entry new_entry = newEntry(-1, -2.5);
    prepend(L, new_entry);
    printList(L);

    moveFront(L);
    moveNext(L);
    set(L, new_entry);
    printList(L);

    int sum_column = ((Entry)back(L))->Column + 5;
    double sum_value = ((Entry)back(L))->Value + 5.0;
    Entry sum_entry = newEntry(sum_column, sum_value);
    append(L, sum_entry);
    printList(L);

    int insert_column = ((Entry)front(L))->Column - 2;
    double insert_value = ((Entry)front(L))->Value - 2.0;
    Entry insert_entry = newEntry(insert_column, insert_value);
    prepend(L, insert_entry);
    printList(L);

    delete(L);
    printList(L);

    moveFront(L);
    delete(L);
    printList(L);

    moveBack(L);
    delete(L);
    printList(L);

    // Test copyList
    List M = copyList(L);
    printList(M);

    clear(L);
    printList(L);

    freeList(&L);
    freeList(&M);

    // Free all entries created
    for (int i = 0; i < 5; i++) {
        free(entries[i]);
    }
    free(new_entry);
    free(sum_entry);
    free(insert_entry);

    return 0;
}