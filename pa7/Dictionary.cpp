/**
 * Dictionary.cpp
 * CSE 101 PA7
 * Zihua Li, CruzID: zli487
 **/


#include "Dictionary.h"
#include <stdexcept>

Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if(R == nullptr) return;
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string &s, Node *R) const {
    if(R == nullptr) return;
    s += R->key + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if(R == N) return;
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node *R) {
    if(R != nil && R != nullptr) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        R = nullptr;
        num_pairs--;
    }
}

Dictionary::Node* Dictionary::search(Node *R, keyType k) const {
    while(R != nullptr && R->key != k) {
        if (R->key > k) R = R->left;
        else R = R->right;
    } return (R == nullptr) ? nil : R;
}

Dictionary::Node* Dictionary::findMin(Node *R) {
    while(R->left != nullptr) R = R->left;
    return R;
}

Dictionary::Node* Dictionary::findMax(Node *R) {
    while(R->right != nullptr) R = R->right;
    return R;
}

Dictionary::Node* Dictionary::findNext(Node *N) {
    if(N == nil || N == nullptr) return nil;
    if(N->right != nullptr) return findMin(N->right);
    Node* N_parent = N->parent;
    while(N_parent != nullptr && N_parent->right == N) {
        N = N_parent;
        N_parent = N_parent->parent;
    }
    if (N_parent == nullptr) return nil;
    else return N_parent;
}

Dictionary::Node* Dictionary::findPrev(Node *N) {
    if(N == nil || N == nullptr) return nil;
    if(N->left != nullptr) return findMax(N->left);
    Node* N_parent = N->parent;
    while(N_parent != nullptr && N_parent->left == N) {
        N = N_parent;
        N_parent = N_parent->parent;
    }
    if (N_parent == nullptr) return nil;
    else return N_parent;
}

Dictionary::Dictionary() : nil(new Node("NIL", -1)), root(nullptr), current(nil), num_pairs(0) {}

Dictionary::Dictionary(const Dictionary &D) : nil(new Node("NIL", -1)), root(nullptr), current(nil), num_pairs(0) {
    preOrderCopy(D.root, nullptr);
}

Dictionary::~Dictionary() {
    clear();
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
    root = nullptr;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* Z = nullptr;
    Node* M = nullptr;
    Node* N = root;
    while (N != nullptr) {
        M = N;
        if (k == N->key) {
            N->val = v;
            return;
        }
        N = (k < N->key) ? N->left : N->right;
    }
    Z = new Node(k, v);
    Z->parent = M;
    if (M == nullptr) root = Z;
    else if (k < M->key) M->left = Z;
    else M->right = Z;
    num_pairs++;
}

void Dictionary::remove(keyType k) {
    Node* N_k = search(root, k);
    if(N_k == nil || N_k == nullptr) throw std::logic_error("remove k is nil");
    if (N_k->right == nullptr){
        if(N_k->parent == nullptr) root = N_k->left;
        else if(N_k == N_k->parent->left) N_k->parent->left = N_k->left;
        else N_k->parent->right = N_k->left;
        if(N_k->left != nullptr) N_k->left->parent = N_k->parent;
        num_pairs--;
    } else if(N_k->left == nullptr){
        if(N_k->parent == nullptr) root = N_k->right;
        else if(N_k == N_k->parent->left) N_k->parent->left = N_k->right;
        else N_k->parent->right = N_k->right;
        if(N_k->right != nullptr) N_k->right->parent = N_k->parent;
        num_pairs--;
    } else {
        Node* N_k_right_min = findMin(N_k->right);
        if(N_k_right_min->parent != N_k){
            if(N_k_right_min->parent == nullptr) root = N_k_right_min->right;
            else if(N_k_right_min == N_k_right_min->parent->left) N_k_right_min->parent->left = N_k_right_min->right;
            else N_k_right_min->parent->right = N_k_right_min->right;
            if(N_k_right_min->right != nullptr) N_k_right_min->right->parent = N_k_right_min->parent;
            N_k_right_min->right = N_k->right;
            N_k_right_min->right->parent = N_k_right_min;
        }
        if(N_k->parent == nullptr) root = N_k_right_min;
        else if(N_k == N_k->parent->left) N_k->parent->left = N_k_right_min;
        else N_k->parent->right = N_k_right_min;
        if(N_k_right_min != nullptr) N_k_right_min->parent = N_k->parent;
        N_k_right_min->left = N_k->left;
        N_k_right_min->left->parent = N_k_right_min;
        num_pairs--;
    }
    if(N_k->parent != nullptr && N_k->parent->left == N_k) N_k->parent->left = nullptr;
    else if(N_k->parent != nullptr && N_k->parent->right == N_k) N_k->parent->right = nullptr;
    if(N_k == current) current = nil;
    delete N_k;
    N_k = nullptr;
}

void Dictionary::begin() { if(root != nil && root != nullptr) current = findMin(root); }

void Dictionary::end() { if(root != nil && root != nullptr) current = findMax(root); }

void Dictionary::next() {
    if(!hasCurrent()) throw std::logic_error("next curr is nil");
    current = findNext(current);
}

void Dictionary::prev() {
    if(!hasCurrent()) throw std::logic_error("prev curr is nil");
    current = findPrev(current);
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
