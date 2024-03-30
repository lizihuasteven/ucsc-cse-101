/**
 * List.cpp
 * CSE 101 PA5
 * Zihua Li, CruzID: zli487
 **/

#include "List.h"
#include <cstdio>
#include <cstdlib>

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    frontDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    for(Node *temp = L.frontDummy->next; temp != L.backDummy; temp = temp->next) {
        this->insertAfter(temp->data);
        moveNext();
    }
    moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if(length() <= 0) {
        fprintf(stderr, "front() empty list.");
        exit(1);
    }
    return frontDummy->next->data;
}

ListElement List::back() const {
    if(length() <= 0) {
        fprintf(stderr, "back() empty list.");
        exit(1);
    }
    return backDummy->prev->data;
}

int List::position() const {
    if(pos_cursor < 0 || pos_cursor > length()) {
        fprintf(stderr, "position() invalid cursor position.");
        exit(1);
    }
    return pos_cursor;
}

ListElement List::peekNext() const {
    if(pos_cursor >= length()) {
        fprintf(stderr, "peekNext() invalid cursor position.");
        exit(1);
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (pos_cursor <= 0) {
        fprintf(stderr, "peekPrev() invalid cursor position.");
        exit(1);
    }
    return beforeCursor->data;
}

void List::clear() {
    for(moveFront(); length() > 0; ) {
        eraseAfter();
    }
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements; //length();
}

ListElement List::moveNext() {
    if (pos_cursor > length()) {
        fprintf(stderr, "moveNext() invalid cursor position.");
        exit(1);
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (pos_cursor < 0) {
        fprintf(stderr, "movePrev() invalid cursor position.");
        exit(1);
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertBefore(ListElement x) {
    if(pos_cursor < 0) {
        fprintf(stderr, "insertBefore() invalid cursor position.");
        exit(EXIT_FAILURE);
    }
    if(afterCursor == nullptr || beforeCursor == nullptr) {
        fprintf(stderr, "insertBefore() afterCursor/beforeCursor is NULL.");
        exit(EXIT_FAILURE);
    }
    Node *newNode = new Node(x);

    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    newNode->next = afterCursor;

    if (afterCursor != nullptr) {  // Add null-check for afterCursor
        afterCursor->prev = newNode;
    }


    beforeCursor = newNode;  // Update beforeCursor to the newly inserted node.

    pos_cursor++;
    num_elements++;
}

void List::insertAfter(ListElement x) {
    if(pos_cursor < 0) {
        fprintf(stderr, "insertAfter() invalid cursor position.");
        exit(1);
    } else if(afterCursor == nullptr || beforeCursor == nullptr) {
        fprintf(stderr, "insertAfter() afterCursor/beforeCursor is NULL.");
        exit(1);
    }
    Node *newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    afterCursor = newNode;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if(pos_cursor > length()) {
        fprintf(stderr, "setAfter() invalid cursor position.");
        exit(1);
    }
    afterCursor->next->data = x;
}

void List::setBefore(ListElement x) {
    if(pos_cursor < 0) {
        fprintf(stderr, "setBefore() invalid cursor position.");
        exit(1);
    }
    beforeCursor->prev->data = x;
}


void List::eraseAfter() {
    if (afterCursor == nullptr || afterCursor == backDummy || pos_cursor > length()) {
        fprintf(stderr, "eraseAfter() invalid cursor position.");
        exit(1);
    }
    Node *temp = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor = temp->next;
    temp->next->prev = beforeCursor;
    delete temp;
    num_elements--;
}

void List::eraseBefore() {
    if (beforeCursor == nullptr || pos_cursor <= 0) {
        fprintf(stderr, "eraseBefore() invalid cursor position.");
        exit(1);
    }
    Node *delRef = beforeCursor;
    beforeCursor = delRef->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    delete delRef;
    pos_cursor--;
    num_elements--;
}

int List::findNext(ListElement x) {
    int count = pos_cursor + 1;
    Node *temp = afterCursor;
    while (temp != backDummy) {
        if (temp->data == x) {
            beforeCursor = temp;
            afterCursor = temp->next;
            pos_cursor = count;
            return pos_cursor;
        }
        temp = temp->next;
        count++;
    }
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
    return -1;
}

int List::findPrev(ListElement x) {
    int count = pos_cursor - 1;
    Node *temp = beforeCursor;
    while (temp != frontDummy) {
        if (temp->data == x) {
            afterCursor = temp;
            beforeCursor = temp->prev;
            pos_cursor = count;
            return pos_cursor;
        }
        temp = temp->prev;
        count--;
    }
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
    pos_cursor = 0;
    return -1;
}


void List::cleanup() {
    int pos = 0;
    for(Node* cursor = frontDummy->next; cursor != backDummy; cursor = cursor->next) {
        Node* current = cursor;
        Node* NextNode = current->next;
        for(int inner_pos = pos + 1; NextNode != backDummy; inner_pos++) {
            if (cursor->data == NextNode->data) {
                if (inner_pos == pos_cursor) { // If the current node is the cursor node
                    beforeCursor = current; // adjust beforeCursor pointer
                    pos_cursor--; // decrement pos_cursor to account for the deleted duplicate
                }
                current->next = NextNode->next;
                NextNode->next->prev = current;
                Node* toDelete = NextNode;
                NextNode = current->next;
                delete toDelete;
                num_elements--;
                if (inner_pos <= pos_cursor) pos_cursor--;
            } else {
                current = NextNode;
                NextNode = NextNode->next;
            }
        }
        pos++;
    }
}


List List::concat(const List &L) const {
    List newList;
    newList.moveBack();
    Node* N;
    for(N = frontDummy->next; N != backDummy; N = N->next) newList.insertBefore(N->data);
    for(N = L.frontDummy->next; N != L.backDummy; N = N->next) newList.insertBefore(N->data);
    newList.beforeCursor = newList.frontDummy;
    newList.afterCursor = newList.beforeCursor->next;
    newList.pos_cursor = 0;
    return newList;
}

std::string List::to_string() const {
    std::string result;
    Node *current = frontDummy->next;
    while (current != backDummy) {
        result += std::to_string(current->data) + " ";
        current = current->next;
    }
    return result;
}

bool List::equals(const List &R) const {
    if(this == &R) return true;
    if (length() != R.length()) {
        return false;
    }
    Node *currL = frontDummy;
    Node *currR = R.frontDummy;
    int i = 0;
    while(i < length()) {
        if (currL->data != currR->data) return false;
        currL = currL->next;
        currR = currR->next;
        i++;
    } return true;
}

std::ostream& operator<<( std::ostream& stream, const List& L ) {
    List::Node *temp = L.frontDummy->next;
    for(; temp != L.backDummy; temp = temp->next) {
        stream << temp->data << " ";
    }
    return stream;
}

bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

#include <algorithm> // for std::swap

List& List::operator=(const List& L) {
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}

/*
int main() {
    List B;
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(5);
    B.insertBefore(12);
    if (B.length() != 5)
        printf("shit!!!!");
    B.clear();

    List A;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);

    A.movePrev();
    printf("movePrev ok!\n");
    fflush(stdout);
    A.eraseAfter();
    printf("eraseAfter ok!\n");
    fflush(stdout);
    if (A.length() != 4)
        printf("Alength != 4");

    A.findPrev(2);
    A.eraseAfter();
    if (A.length() != 3)
        printf("Alength != 3");

    A.clear();

    List C;
    C.insertBefore(1);
    C.insertBefore(2);
    C.insertBefore(3);
    C.insertBefore(5);
    C.insertBefore(12);

    C.movePrev();
    C.eraseAfter();
    if (C.length() != 4)
        printf("error Clength!=4");

    C.findPrev(2);
    C.eraseAfter();
    if (C.length() != 3)
        printf("error Clength!=3");

    fflush(stdout);
    C.clear();

    return 0;
}
 */