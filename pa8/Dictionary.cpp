/**
 * Dictionary.cpp
 * CSE 101 PA8
 * Zihua Li, CruzID: zli487
 **/

#define RED 1
#define BLACK 2

#include "Dictionary.h"
#include <stdexcept>

Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if(R == nullptr || R == nil) return;
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string &s, Node *R) const {
    if(R == nullptr || R == nil) return;
    s += R->key + (R->color == RED ? " (RED)" : "") + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if(R == nullptr || R == N) return;
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node *R) {
    if(R != nullptr && R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node *R, keyType k) const {
    while(R != nil && R->key != k) {
        if (R->key > k) R = R->left;
        else R = R->right;
    } return R;
}

Dictionary::Node* Dictionary::findMin(Node *R) {
    while(R->left != nil) R = R->left;
    return R;
}

Dictionary::Node* Dictionary::findMax(Node *R) {
    while(R->right != nil) R = R->right;
    return R;
}

Dictionary::Node* Dictionary::findNext(Node *N) {
    if(N->right != nil) return findMin(N->right);
    Node* N_parent = N->parent;
    while(N_parent != nil && N_parent->right == N) {
        N = N_parent;
        N_parent = N_parent->parent;
    } return (N_parent == nil) ? nil : N_parent;
}

Dictionary::Node* Dictionary::findPrev(Node *N) {
    if(N->left != nil) return findMax(N->left);
    Node* N_parent = N->parent;
    while(N_parent != nil && N_parent->left == N) {
        N = N_parent;
        N_parent = N_parent->parent;
    } return (N_parent == nil) ? nil : N_parent;
}

void Dictionary::LeftRotate(Node *N) {
    Node* N_right = N->right;
    N->right = N_right->left;
    if (N_right->left != nil) N_right->left->parent = N;
    N_right->parent = N->parent;
    if (N->parent == nil) root = N_right;
    else if (N != N->parent->left) N->parent->right = N_right; else N->parent->left = N_right;
    N_right->left = N;
    N->parent = N_right;
}

void Dictionary::RightRotate(Node *N) {
    Node* N_left = N->left;
    N->left = N_left->right;
    if (N_left->right != nil) N_left->right->parent = N;
    N_left->parent = N->parent;
    if (N->parent == nil) root = N_left;
    else { if (N != N->parent->right) N->parent->left = N_left; else N->parent->right = N_left; }
    N_left->right = N;
    N->parent = N_left;
}

void Dictionary::RB_InsertFixUp(Node *N) {
    while (N->parent != nullptr && N->parent != nil && N->parent->color != BLACK) {
        if (N->parent != N->parent->parent->left) {
            Node* N_uncle = N->parent->parent->left;
            if (N_uncle->color != BLACK) {
                N->parent->color = BLACK;
                N_uncle->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        } else {
            Node* N_uncle = N->parent->parent->right;
            if (N_uncle->color != BLACK) {
                N->parent->color = BLACK;
                N_uncle->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
    } root->color = BLACK;
}

void Dictionary::RB_Transplant(Node *u, Node *v) {
    if (u->parent == nil) root = v;
    else { if (u != u->parent->left) u->parent->right = v; else u->parent->left = v; }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != nullptr && N != root && N->color != RED) {
        if (N != N->parent->left) {
            Node* N_sibling = N->parent->left;
            if (N_sibling->color != BLACK) {
                N_sibling->color = BLACK;
                N_sibling = N->parent->left;
                RightRotate(N->parent);
                N->parent->color = RED;
            }
            if (N_sibling->right->color != RED && N_sibling->left->color != RED) {
                N_sibling->color = RED;
                N = N->parent;
            } else {
                if (N_sibling->left->color != RED) {
                    N_sibling->color = RED;
                    N_sibling->right->color = BLACK;
                    LeftRotate(N_sibling);
                    N_sibling = N->parent->left;
                }
                N_sibling->color = N->parent->color;
                N_sibling->left->color = BLACK;
                N->parent->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        } else {
            Node* N_sibling = N->parent->right;
            if (N_sibling->color != BLACK) {
                N_sibling->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                N_sibling = N->parent->right;
            }
            if (N_sibling->left->color == BLACK && N_sibling->right->color != RED) {
                N = N->parent;
                N_sibling->color = RED;
            } else {
                if (N_sibling->right->color != RED) {
                    N_sibling->left->color = BLACK;
                    N_sibling->color = RED;
                    RightRotate(N_sibling);
                    N_sibling = N->parent->right;
                }
                N_sibling->color = N->parent->color;
                N->parent->color = BLACK;
                N_sibling->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
    } if (N != nullptr) N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N) {
    if (N == nullptr || N == nil) return;
    Node* N_replace;
    Node* N_to_fix = N;
    int original_color = N_to_fix->color;
    if (N->right == nil) {
        N_replace = N->left;
        RB_Transplant(N, N->left);
    } else if (N->left == nil) {
        N_replace = N->right;
        RB_Transplant(N, N->right);
    } else {
        N_to_fix = findMin(N->right);
        N_replace = N_to_fix->right;
        original_color = N_to_fix->color;
        if (N_to_fix->parent != N) {
            RB_Transplant(N_to_fix, N_to_fix->right);
            N_to_fix->right = N->right;
            N_to_fix->right->parent = N_to_fix;
        } else N_replace->parent = N_to_fix;
        RB_Transplant(N, N_to_fix);
        N_to_fix->left = N->left;
        N_to_fix->left->parent = N_to_fix;
        N_to_fix->color = N->color;
    }
    if (original_color == BLACK) RB_DeleteFixUp(N_replace);
    delete N;
}

Dictionary::Dictionary() : nil(new Node("NIL", -1)), root(nil), current(nil), num_pairs(0) {
    nil->color = BLACK;
}

Dictionary::Dictionary(const Dictionary &D) : nil(new Node("NIL", -1)), root(nil), current(nil), num_pairs(0) {
    nil->color = BLACK;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
    nil = nullptr, root = nullptr, current = nullptr;
}

int Dictionary::size() const { return num_pairs; }

bool Dictionary::contains(keyType k) const { return (search(root, k) != nil); }

valType& Dictionary::getValue(keyType k) const {
    Node* N_k = search(root, k);
    if(N_k == nil) throw std::logic_error("getValue k is nil");
    return N_k->val;
}

bool Dictionary::hasCurrent() const { return (current != nil); }

keyType Dictionary::currentKey() const {
    if(!hasCurrent()) throw std::logic_error("currentKey current is nil");
    return current->key;
}

valType& Dictionary::currentVal() const {
    if(!hasCurrent()) throw std::logic_error("currentVal current is nil");
    return current->val;
}

void Dictionary::clear() {
    postOrderDelete(root);
    current = nil;
    root = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* N_A = root;
    Node* N_B = nil;
    while (N_A != nil) {
        N_B = N_A;
        if (k < N_A->key) N_A = N_A->left;
        else {
            if (k > N_A->key) N_A = N_A->right;
            else {
                N_A->val = v;
                return;
            }
        }
    }
    Node* N_C = new Node(k, v);
    N_C->left = nil;
    N_C->right = nil;
    N_C->parent = N_B;
    N_C->color = RED;
    if (N_B == nil) root = N_C;
    else { if (k < N_B->key) N_B->left = N_C; else N_B->right = N_C; }
    num_pairs++;
    RB_InsertFixUp(N_C);
}


void Dictionary::remove(keyType k) {
    Node* N_k = search(root, k);
    if(N_k == nullptr || N_k == nil) throw std::logic_error("remove: k is nil");
    if(N_k == current) current = nil;
    RB_Delete(N_k);
    num_pairs--;
}

void Dictionary::begin() { if(num_pairs > 0) current = findMin(root); }

void Dictionary::end() { if(num_pairs > 0) current = findMax(root); }

void Dictionary::next() {
    Node* N_next = findNext(current);
    if(N_next != nullptr && N_next != nil) current = N_next;
    else current = nil;
}

void Dictionary::prev() {
    Node* N_prev = findPrev(current);
    if(N_prev != nullptr && N_prev != nil) current = N_prev;
    else current = nil;
}

std::string Dictionary::to_string() const {
    std::string S;
    inOrderString(S, root);
    return S;
}

std::string Dictionary::pre_string() const {
    std::string S;
    preOrderString(S, root);
    return S;
}

bool Dictionary::equals(const Dictionary& D) const { return (to_string() == D.to_string()); }

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) { return stream << D.to_string(); }

bool operator==( const Dictionary& A, const Dictionary& B ) { return A.equals(B); }

Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if(this == &D) return *this;
    Dictionary D_temp = D;
    std::swap(root, D_temp.root);
    std::swap(current, D_temp.current);
    std::swap(num_pairs, D_temp.num_pairs);
    std::swap(nil, D_temp.nil);
    return *this;
}

/*
int main() {
    Dictionary A, B;
    printf("size is %d\n", A.size());
    A.setValue("c", 3);
    A.setValue("a", 1);
    A.setValue("b", 2);
    A.remove("a");
    printf("size is %d\n", A.size());
    A.setValue("e", 5);
    A.remove("c");
    printf("size is %d\n", A.size());
    A.clear();



    A.setValue("d", 1);
    A.setValue("b", 5);
    A.setValue("c", 16);
    A.setValue("f", 176);
    A.setValue("e", 3214);
    A.end();
*/
