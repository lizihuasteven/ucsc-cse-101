/*

Zihua Li, CruzID: zli487
ListTest.c tests all the ADT functions declared in List.h
PA1, CSE 101 Winter 2024

*/


#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // 创建列表并测试 newList 和 freeList
    List L = newList();
    if (L != NULL) printf("newList passed.\n");
    else printf("newList failed.\n");

    // 测试 append 和 length
    append(L, 10);
    append(L, 20);
    append(L, 30);
    if (length(L) == 3) printf("append and length passed.\n");
    else printf("append or length failed.\n");

    // 测试 prepend
    prepend(L, 5);
    if (front(L) == 5) printf("prepend passed.\n");
    else printf("prepend failed.\n");

    // 测试 moveFront, moveBack, movePrev, moveNext
    moveFront(L);
    if (get(L) == 5) printf("moveFront passed.\n");
    else printf("moveFront failed.\n");

    moveBack(L);
    if (get(L) == 30) printf("moveBack passed.\n");
    else printf("moveBack failed.\n");

    movePrev(L);
    if (get(L) == 20) printf("movePrev passed.\n");
    else printf("movePrev failed.\n");

    moveNext(L);
    if (get(L) == 30) printf("moveNext passed.\n");
    else printf("moveNext failed.\n");

    // 测试 set
    moveFront(L);
    set(L, 25);
    if (get(L) == 25) printf("set passed.\n");
    else printf("set failed.\n");

    // 测试 insertBefore, insertAfter
    insertBefore(L, 15);
    movePrev(L);
    if (get(L) == 15) printf("insertBefore passed.\n");
    else printf("insertBefore failed.\n");

    insertAfter(L, 17);
    moveNext(L);
    if (get(L) == 17) printf("insertAfter passed.\n");
    else printf("insertAfter failed.\n");

    // 测试 deleteFront, deleteBack
    deleteFront(L);
    if (front(L) != 5) printf("deleteFront passed.\n");
    else printf("deleteFront failed.\n");

    deleteBack(L);
    if (back(L) != 30) printf("deleteBack passed.\n");
    else printf("deleteBack failed.\n");

    // 测试 delete
    moveFront(L);
    delete(L);
    if (length(L) == 3) printf("delete passed.\n");
    else printf("delete failed.\n");

    // 测试 clear
    clear(L);
    if (length(L) == 0) printf("clear passed.\n");
    else printf("clear failed.\n");

    // 测试 equals 和 copyList
    append(L, 40);
    append(L, 50);
    List L2 = copyList(L);
    if (equals(L, L2)) printf("copyList and equals passed.\n");
    else printf("copyList or equals failed.\n");

    // 清理资源
    freeList(&L);
    freeList(&L2);

    printf("All tests completed.\n");
    return 0;
}
