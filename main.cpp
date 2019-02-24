#include <iostream>

#include "rules.h"

int main() {
    // beg;fin;movs;porin;porout;numOp;op1_num11_num12;op2_num21_num22;op3_num31_num32;op4_num41_num42;op5_num51_num52;
    // none, sign, reverse, sum, del, shiftr, shiftl, mirror, inv, store
    // add, subtract, multiply, divide, newdig, power, extra
    // replace
    std::string inputstr;

    std::cout << "none, sign, reverse, sum, del, shiftr, shiftl, mirror, inv, store"
              << std::endl
              << "add, subtract, multiply, divide, newdig, power, extra"
              << std::endl
              << "replace"
              << std::endl
              << "beg;fin;movs;porin;porout;numOp;op1_num11_num12;op2_num21_num22;op3_num31_num32;op4_num41_num42;op5_num51_num52;"
              << std::endl
              << ";;;;;;__;__;__;__;__;"
              << std::endl;

    std::cin >> inputstr;

    rules test(inputstr);
    test.calc();
    test.print();

    return 0;
}