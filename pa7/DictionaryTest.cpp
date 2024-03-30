/**
 * DictionaryTest.cpp
 * CSE 101 PA7
 * Zihua Li, CruzID: zli487
 **/

#include <cstdio>
#include "Dictionary.h"

int main() {
    Dictionary A, B;

    // 测试构造函数和size()
    if(A.size() != 0) printf("A size is not 0!\n");

    // 测试setValue() 和 size()
    A.setValue("a", 1);
    A.setValue("b", 2);
    A.setValue("c", 3);
    A.setValue("e", 5);
    if(A.size() != 4) printf("A setValue or size failed\n");

    // 测试remove()
    A.remove("a");
    A.remove("b");
    A.remove("c");
    A.remove("e");
    if(A.size() != 0) printf("A remove or size failed\n");

    // 重新添加元素并测试contains()
    A.setValue("c", 3);
    if(!A.contains("c")) printf("A contains failed\n");

    // 测试getValue()
    try {
        if(A.getValue("c") != 3) printf("A getValue failed\n");
    } catch (...) {
        printf("A getValue exception\n");
    }

    // 测试hasCurrent()、currentKey() 和 currentVal() 在设置值后
    A.setValue("a", 1);
    A.setValue("b", 2);
    A.begin();
    if(!A.hasCurrent()) printf("A hasCurrent (after begin) failed\n");
    if(A.currentKey() != "a") printf("A currentKey failed\n");
    if(A.currentVal() != 1) printf("A currentVal failed\n");

    // 测试next() 和 prev()
    A.next();
    if(A.currentKey() != "b") printf("A next failed\n");
    A.prev();
    if(A.currentKey() != "a") printf("A prev failed\n");

    // 测试end()
    A.end();
    if(A.currentKey() != "c") printf("A end failed\n");

    // 测试复制构造函数和equals()
    Dictionary C = A;
    if(!C.equals(A)) printf("Copy constructor or equals failed\n");

    // 测试to_string() 和 pre_string() 的简单形式（完整测试取决于具体实现）
    if(A.to_string().empty()) printf("A to_string failed\n");
    if(A.pre_string().empty()) printf("A pre_string failed\n");

    // 测试删除和再次验证
    A.remove("a");
    if(A.size() != 2) printf("A remove (after re-addition) failed\n");
    A.setValue("e", 5);
    A.remove("c");
    if(A.size() != 2) printf("A remove or setValue (after re-addition) failed\n");

    return 0;
}
