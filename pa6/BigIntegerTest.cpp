/**
 * BigIntegerTest.cpp
 * CSE 101 PA6
 * Zihua Li, CruzID: zli487
 **/

#include "BigInteger.h"

int main() {
    // 测试默认构造函数
    BigInteger defaultBigInteger;
    std::cout << "Default BigInteger sign: " << defaultBigInteger.sign() << std::endl;

    // 测试long构造函数
    BigInteger positiveBigInteger(123456789);
    BigInteger negativeBigInteger(-987654321);
    BigInteger zeroBigInteger(0);

    std::cout << "Positive BigInteger sign: " << positiveBigInteger.sign() << std::endl;
    std::cout << "Negative BigInteger sign: " << negativeBigInteger.sign() << std::endl;
    std::cout << "Zero BigInteger sign: " << zeroBigInteger.sign() << std::endl;

    // 测试字符串构造函数
    BigInteger strPositiveBigInteger("123456789");
    BigInteger strNegativeBigInteger("-987654321");
    BigInteger strZeroBigInteger("0");

    try {
        BigInteger invalidBigInteger("abc123");
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught exception for invalid string: " << e.what() << std::endl;
    }

    // 测试compare函数
    std::cout << "Comparing positive and negative BigInteger: " << positiveBigInteger.compare(negativeBigInteger) << std::endl;
    std::cout << "Comparing negative and positive BigInteger: " << negativeBigInteger.compare(positiveBigInteger) << std::endl;
    std::cout << "Comparing positive and zero BigInteger: " << positiveBigInteger.compare(zeroBigInteger) << std::endl;
    std::cout << "Comparing zero and negative BigInteger: " << zeroBigInteger.compare(negativeBigInteger) << std::endl;
    std::cout << "Comparing two zeros: " << zeroBigInteger.compare(strZeroBigInteger) << std::endl;

    // 测试makeZero和negate函数
    positiveBigInteger.makeZero();
    std::cout << "After makeZero, positive BigInteger sign: " << positiveBigInteger.sign() << std::endl;

    negativeBigInteger.negate();
    std::cout << "After negate, negative BigInteger sign: " << negativeBigInteger.sign() << std::endl;

    // 加法测试

    // sum up positive nums
    BigInteger posLarge(100);
    BigInteger posSmall(50);
    std::cout << "100 + 50 = " << posLarge.add(posSmall).to_string() << std::endl;

    // sum up positive nums
    std::cout << "50 + 100 = " << posSmall.add(posLarge).to_string() << std::endl;

    // sum up positive nums
    std::cout << "50 + 50 = " << posSmall.add(posSmall).to_string() << std::endl;

    // sum up negative numbers
    BigInteger negLarge(-100);
    BigInteger negSmall(-50);
    std::cout << "-100 + (-50) = " << negLarge.add(negSmall).to_string() << std::endl;
    std::cout << "-50 + (-100) = " << negSmall.add(negLarge).to_string() << std::endl;

    // sum up pos and neg
    std::cout << "100 + (-50) = " << posLarge.add(negSmall).to_string() << std::endl;

    // sum up neg and pos
    std::cout << "-50 + 100 = " << negSmall.add(posLarge).to_string() << std::endl;

    // sum up pos and zero
    BigInteger zero(0);
    std::cout << "100 + 0 = " << posLarge.add(zero).to_string() << std::endl;
    std::cout << "0 + 100 = " << zero.add(posLarge).to_string() << std::endl;

    // sum up neg and zero
    std::cout << "-100 + 0 = " << negLarge.add(zero).to_string() << std::endl;
    std::cout << "0 + (-100) = " << zero.add(negLarge).to_string() << std::endl;

    // sum up zero and zero
    std::cout << "0 + 0 = " << zero.add(zero).to_string() << std::endl;

    // 减法测试

    // 两个正数相减，被减数大于减数
    std::cout << "100 - 50 = " << posLarge.sub(posSmall).to_string() << std::endl;

    // 两个正数相减，被减数小于减数
    std::cout << "50 - 100 = " << posSmall.sub(posLarge).to_string() << std::endl;

    // 两个正数相减，被减数等于减数
    std::cout << "50 - 50 = " << posSmall.sub(posSmall).to_string() << std::endl;

    // 两个负数相减
    std::cout << "-100 - (-50) = " << negLarge.sub(negSmall).to_string() << std::endl;
    std::cout << "-50 - (-100) = " << negSmall.sub(negLarge).to_string() << std::endl;

    // 正数减负数
    std::cout << "100 - (-50) = " << posLarge.sub(negSmall).to_string() << std::endl;

    // 负数减正数
    std::cout << "-50 - 100 = " << negSmall.sub(posLarge).to_string() << std::endl;

    // 其中一个为零的情况
    std::cout << "100 - 0 = " << posLarge.sub(zero).to_string() << std::endl;
    std::cout << "0 - 100 = " << zero.sub(posLarge).to_string() << std::endl;

    // 两个数都为零
    std::cout << "0 - 0 = " << zero.sub(zero).to_string() << std::endl;

    // mult test
    std::cout << "100 * 50 = " << posLarge.mult(posSmall).to_string() << std::endl;
    std::cout << "50 * 100 = " << posSmall.mult(posLarge).to_string() << std::endl;
    std::cout << "50 * 50 = " << posSmall.mult(posSmall).to_string() << std::endl;
    std::cout << "-100 * 50 = " << negLarge.mult(posSmall).to_string() << std::endl;
    std::cout << "50 * -100 = " << posSmall.mult(negLarge).to_string() << std::endl;
    std::cout << "-50 * -50 = " << negSmall.mult(negSmall).to_string() << std::endl;
    std::cout << "100 * -50 = " << posLarge.mult(negSmall).to_string() << std::endl;
    std::cout << "-50 * 100 = " << negSmall.mult(posLarge).to_string() << std::endl;


    BigInteger A = BigInteger("+111122223333");
    BigInteger B = BigInteger("+222211110000");
    //BigInteger C = BigInteger(222211110000);

    // pos + pos = pos
    BigInteger D = BigInteger("+333333333333");
    BigInteger C = A + B;

    if (!(C == D)) std::cout << "C=DERROR!!!\n";

    B = BigInteger("-111122223333");
    C = A + B;
    if (C.sign() != 0) std::cout << "C.signERROR!!!\n";

    //-> pos + neg > 0
    B = BigInteger("-110122223333");
    //std::cout << "B is " << B.BigInteger::to_string() << std::endl;
    D = BigInteger("1000000000");
    C = A + B;
    if (A.compare(B) == 0) std::cout << "ERROR!!!!!!!!!";
    if (A.compare(B) > 0) std::cout << "GOOD!!!!\n";
    if (C.sign() != 1)
        std::cout << "Error: C is " << A.add(B).to_string() << std::endl;
    if (!(C == D))
        std::cout << "ERROR!!!";

    //mult test
    A = BigInteger("111122223333");
    B = BigInteger("111122223333");
    C = BigInteger();
    D = BigInteger("12348148518469129628889");
    std::cout << "Goo!!!\n";
    std::cout << "C is " << A.mult(B).to_string() << std::endl;
    // pos * pos = pos
    C = A * B;
    std::cout << "Goo!!!";
    if (C.sign() != 1)
        std::cout << "ERROR!!!\n";
    else std::cout << "Good!!!\n";
    if (!(C == D))
        std::cout << "ERROR!!!\n";
    else std::cout << "Good!!!\n";

    std::cout << "Start add Test extra\n";

    A = BigInteger("-0000000000041085449");
    B = BigInteger("6402779357");
    C = A + B;

    std::cout << "Start sub Test extra\n";
    C = A - B;

    A = BigInteger("+2276000000000000000000000101580000000000000000000073235000000000000000000000379054691648041393022029");
    B = BigInteger("+9521651023449965519405564118547355094880066777565423238991085675906554459642294029683201863865856036");
    BigInteger three = BigInteger(3);
    std::cout << "3A is " << A.mult(three).to_string() << std::endl;
    std::cout << "3B is " << B.mult(three).to_string() << std::endl;

    return 0;
}