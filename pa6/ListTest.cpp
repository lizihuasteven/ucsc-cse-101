/**
 * ListTest.cpp
 * CSE 101 PA6
 * Zihua Li, CruzID: zli487
 **/

#include <cassert>
#include "List.h"

int main() {
    // Test 1: Empty list
    {
        List A;
        assert(A.length() == 0);
        assert(A.position() == 0);
        printf("Test 1: Empty list passed.\n");
    }

    // Test 2: InsertAfter
    {
        List A;
        A.insertAfter(10);
        assert(A.length() == 1);
        assert(A.position() == 0);

        A.insertAfter(20);
        assert(A.length() == 2);
        assert(A.position() == 0);

        A.insertAfter(30);
        assert(A.length() == 3);
        assert(A.position() == 0);
        printf("Test 2: InsertAfter passed.\n");
    }

    // Test 3: InsertBefore
    {
        List A;
        A.insertBefore(10);
        assert(A.length() == 1);
        assert(A.position() == 1);

        A.insertBefore(20);
        assert(A.length() == 2);
        assert(A.position() == 2);

        A.insertBefore(30);
        assert(A.length() == 3);
        assert(A.position() == 3);
        printf("Test 3: InsertBefore passed.\n");
    }

    // Test 4: eraseAfter
    {
        List A;
        A.insertBefore(10);
        A.insertBefore(20);
        A.insertBefore(30);

        A.movePrev();
        A.eraseAfter();
        assert(A.length() == 2);
        printf("Test 4: eraseAfter passed.\n");
    }

    // Test 5: eraseBefore
    {
        List A;
        A.insertAfter(10);
        A.insertAfter(20);
        A.insertAfter(30);

        A.moveNext();
        A.eraseBefore();
        assert(A.length() == 2);
        printf("Test 5: eraseBefore passed.\n");
    }

    // Test 6: Check position of elements after multiple operations
    {
        List A;
        A.insertAfter(10);
        A.insertAfter(20);
        A.insertAfter(30);
        assert(A.position() == 0);

        A.moveFront();
        assert(A.position() == 0);
        A.moveNext();
        assert(A.position() == 1);
        printf("Test 6: Position check passed.\n");
    }

    // Test 7: FindNext function
    {
        List A;
        A.insertAfter(60);
        A.insertAfter(50);
        A.insertAfter(40);
        A.insertBefore(10);
        A.insertBefore(20);
        A.insertBefore(30);

        assert(A.findNext(40) != -1);
        assert(A.findNext(10000) == -1);
        printf("Test 7: FindNext Passed.\n");
    }

    // Test 8: eraseAfter and eraseBefore
    {
        List A;
        A.insertAfter(50);
        A.insertBefore(60);
        A.eraseAfter();
        A.eraseBefore();

        assert(A.length() == 0);
        printf("Test 8: EraseAfter and eraseBefore passed.\n");
    }

    // Test 9: equals function
    {
        List A, B;
        A.insertAfter(5);
        A.insertAfter(15);

        B.insertBefore(15);
        B.insertBefore(5);

        assert(A.equals(B));
        printf("Test 9: Equals function passed.\n");
    }

    // Test 10: cleanup function
    {
        List A;
        A.insertAfter(5);
        A.insertAfter(5);
        A.insertBefore(5);
        A.insertBefore(10);

        A.cleanup();

        assert(A.length() == 2);
        printf("Test 10: Cleanup function passed.\n");
    }

    // Test 11: concat function
    {
        List A, B;
        A.insertAfter(10);
        A.insertAfter(20);
        A.insertBefore(30);

        B.insertAfter(40);
        B.insertBefore(50);

        List C = A.concat(B);

        assert(C.length() == 5);
        printf("Test 11: Concat function passed.\n");
    }

    // Test 12: clear function
    {
        List A;
        A.insertAfter(10);
        A.insertAfter(20);
        A.insertBefore(30);

        A.clear();

        assert(A.length() == 0);
        printf("Test 12: Clear function passed.\n");
    }


    printf("All tests passed.\n");
    return 0;
}