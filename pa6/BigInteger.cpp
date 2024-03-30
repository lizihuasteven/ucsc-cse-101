/**
 * BigInteger.cpp
 * CSE 101 PA6
 * Zihua Li, CruzID: zli487
 **/

#include <stdexcept>
#include <cctype>
#include <algorithm>
#include "BigInteger.h"
#include "List.h"

const ListElement base = 1000000000;
const int power = 9;

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
        digits.insertBefore(0);
    } else {
        signum = (x < 0) ? -1 : 1;
        x = (x < 0) ? -x : x;
        while (x > 0) {
            digits.insertBefore(x % base);
            x /= base;
        }
    }
}

BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) throw std::invalid_argument("BigInteger(std::string s) ERR: s is empty.");
    signum = (s[0] == '-') ? -1 : 1;
    int offset = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    for (std::string::size_type i = offset; i < s.length(); i++) {
        if (!isdigit(s[i])) throw std::invalid_argument("BigInteger(std::string s) ERR: s contains non-digit characters.");
    }
    s = s.substr(offset); // Remove sign for conversion
    if (s == "0") {
        signum = 0;
        digits.insertAfter(0);
        return;
    }
    if (s.empty()) throw std::invalid_argument("BigInteger(std::string s) ERR: s contains no digits.");
    digits.moveFront();
    for (int i = s.length(); i > 0; i -= power) {
        int start = std::max(i - power, 0);
        std::string num = s.substr(start, i - start);
        digits.insertBefore(std::stol(num, nullptr, 10));
        digits.moveBack();
    }
    digits.moveBack();
    while (digits.length() > 1 && digits.peekPrev() == 0) {
        digits.eraseBefore();
        digits.moveBack();
    }
}

BigInteger::BigInteger(const BigInteger &N) {
    signum = N.signum;
    digits = N.digits;
}

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum < N.signum) return -1;
    if (signum > N.signum) return 1;
    if (signum == 0 && N.signum == 0) return 0;
    if (digits.length() == N.digits.length()) {
        List L_this = digits;
        List L_N = N.digits;
        L_this.moveBack();
        L_N.moveBack();
        for (int i = 0; i < L_this.length(); i++) {
            if (L_this.peekPrev() < L_N.peekPrev()) return -signum;
            if (L_this.peekPrev() > L_N.peekPrev()) return signum;
            L_this.movePrev();
            L_N.movePrev();
        } return 0; // all digits are equal
    } else return (digits.length() < N.digits.length()) ? -signum : signum; // if signum = -1, greater length makes the integer smaller
}

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum = -signum;
}

BigInteger BigInteger::add(const BigInteger &N) const {
    BigInteger result;
    if (signum == 0) {
        result = N;
        return result;
    } else if (N.signum == 0) {
        result = *this;
        return result;
    } else if (signum == N.signum) {
        List L_result;
        List L_this = digits;
        List L_N = N.digits;
        L_this.moveFront();
        L_N.moveFront();
        int carry = 0;
        while (L_this.position() < L_this.length() && L_N.position() < L_N.length()) {
            int sum = L_this.peekNext() + L_N.peekNext() + carry;
            L_this.moveNext();
            L_N.moveNext();
            carry = sum / base;
            L_result.moveBack();
            L_result.insertBefore(sum % base);
        }
        while (L_this.position() < L_this.length()) {
            int sum = L_this.peekNext() + carry;
            L_this.moveNext();
            carry = sum / base;
            L_result.moveBack();
            L_result.insertBefore(sum % base);
        }
        while (L_N.position() < L_N.length()) {
            int sum = L_N.peekNext() + carry;
            L_N.moveNext();
            carry = sum / base;
            L_result.moveBack();
            L_result.insertBefore(sum % base);
        }
        if (carry > 0) {
            L_result.moveBack();
            L_result.insertBefore(carry);
        }
        result.signum = signum;
        result.digits = L_result;
    } else {
        List L_result;
        List L_this = digits;
        List L_N = N.digits;
        if (signum == 1 && N.signum == -1) {
            BigInteger BI_N_copy = N;
            BI_N_copy.negate();
            result = (*this).sub(BI_N_copy);
            return result;
        } else if (signum == -1 && N.signum == 1) {
            BigInteger BI_this_copy = *this;
            BI_this_copy.negate();
            if (BI_this_copy.compare(N) < 0) {
                result = N.sub(BI_this_copy);
                return result;
            }
            result = BI_this_copy.sub(N);
            result.signum = -(result.signum);
            return result;
        }
    } return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger result;
    int compare_result = (*this).compare(N); // store compare result once and for all
    if (compare_result == 0) {
        result.makeZero();
        result.signum = 0;
        return result;
    }
    if (signum == 0) {
        result = N;
        result.negate();
        return result;
    } else if (N.signum == 0) {
        result = *this;
        return result;
    } else if (signum == N.signum) { // same signums
        List L_this, L_N;
        if (compare_result > 0 && signum == -1) { // if both are negative and this > N, exchange N.digits and digits of L_this and L_N
            L_this = N.digits;
            L_N = digits;
        } else { // exchange N.digits and digits of L_this and L_N if this < N and both are positive
            L_this = (compare_result < 0 && signum == 1) ? N.digits : digits;
            L_N = (compare_result < 0 && signum == 1) ? digits : N.digits;
        }
        List L_result;
        L_this.moveFront();
        L_N.moveFront();
        int carry = 0;
        while (L_this.position() < L_this.length() || L_N.position() < L_N.length()) {
            int a = (L_this.position() < L_this.length()) ? L_this.peekNext() : 0;
            int b = (L_N.position() < L_N.length()) ? L_N.peekNext() : 0;
            if (L_this.position() < L_this.length()) L_this.moveNext();
            if (L_N.position() < L_N.length()) L_N.moveNext();
            int diff = a - b - carry;
            if (diff < 0) {
                diff += base;
                carry = 1;
            } else carry = 0;
            L_result.moveBack();
            L_result.insertBefore(diff);
        }
        L_result.moveBack();
        while (L_result.peekPrev() == 0 && L_result.length() > 1) {
            L_result.eraseBefore();
            L_result.moveBack();
        }
        result.signum = (compare_result < 0 && signum == 1) ? -signum : signum; // if this < N, negate the signum
        if (compare_result > 0 && signum == -1) result.signum = 1; // if both are neg & this>N, result.signum=1
        result.digits = L_result;
    } else { // if they have different signums we just call add()
        if (signum == 1 && N.signum == -1) {
            BigInteger BI_N_copy = N;
            BI_N_copy.negate(); // abs(N)
            result = (*this).add(BI_N_copy);
            return result;
        } else if (signum == -1 && N.signum == 1) {
            BigInteger BI_this_copy = *this;
            BI_this_copy.negate(); // abs(this)
            result = BI_this_copy.add(N);
            result.signum = -1;
            return result;
        }
    } return result;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;
    if ((*this).digits.length() == 0 || N.digits.length() == 0) {
        result.digits.insertAfter(0);
        return result;
    }
    result.signum = this->signum * N.signum; // set result signum
    List L_this = (*this).digits;
    List L_N = N.digits;
    std::vector<long> product(L_this.length() + L_N.length(), 0); // init a vector to store product
    int i = 0;
    for (L_this.moveFront(); L_this.position() < L_this.length(); L_this.moveNext(), i++) {
        long digitA = L_this.peekNext();
        int j = 0;
        for (L_N.moveFront(); L_N.position() < L_N.length(); L_N.moveNext(), j++) {
            long digitB = L_N.peekNext();
            long sum = product[i + j] + digitA * digitB; // calculate product and process carry
            product[i + j] = sum % base;
            product[i + j + 1] += sum / base;
        }
    }
    for (size_t idx = 0; idx < product.size(); idx++) result.digits.insertBefore(product[idx]); // assign product back into BigInteger
    while (result.digits.length() > 1) { // remove unnecessary zeros
        result.digits.moveBack();
        if (result.digits.peekPrev() == 0) result.digits.eraseBefore(); // 假设eraseBefore()存在，用于删除当前位置之前的元素
        else break;
    } return result;
}

std::string BigInteger::to_string(){
    if(signum == 0) return "0";
    std::string S = "";
    if(signum == -1) S += '-';
    for (digits.moveBack(); digits.peekPrev() == 0 && digits.length() > 1; digits.moveBack()) digits.eraseBefore(); // remove leading zeros
    for (digits.moveBack(); digits.position() > 0; digits.movePrev()){
        std::string S_digits = std::to_string(digits.peekPrev());
        std::string S_leading_zeros = "";
        while(digits.position() != digits.length() && (S_digits.length() + S_leading_zeros.length()) < power) S_leading_zeros += "0";
        S += (S_leading_zeros + S_digits);
    } return S;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ) { return stream << N.BigInteger::to_string(); }

bool operator==( const BigInteger& A, const BigInteger& B ) { return (A.compare(B) == 0); }

bool operator<( const BigInteger& A, const BigInteger& B ) { return (A.compare(B) == -1); }

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int compare_result = A.compare(B);
    return (compare_result == -1 || compare_result == 0);
}

bool operator>( const BigInteger& A, const BigInteger& B ) { return (A.compare(B) == 1); }

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int compare_result = A.compare(B);
    return (compare_result == 1 || compare_result == 0);
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) { return A.add(B); }

BigInteger operator+=( BigInteger& A, const BigInteger& B ) { return A = A.add(B); }

BigInteger operator-( const BigInteger& A, const BigInteger& B ) { return A.sub(B); }

BigInteger operator-=( BigInteger& A, const BigInteger& B ) { return A = A.sub(B); }

BigInteger operator*( const BigInteger& A, const BigInteger& B ) { return A.mult(B); }

BigInteger operator*=( BigInteger& A, const BigInteger& B ) { return A = A.mult(B); }