//
// Created by chrisljiang on 2019-02-17.
//

#include <iostream>

#include "rules.h"

int main() {
    // beg;fin;movs;porin;porout;numOp;op1_num11_num12;op2_num21_num22;op3_num31_num32;op4_num41_num42;op5_num51_num52;
    // sig, rev, sum, del, shr, shl, mir, inv, sto
    // add, sub, mul, div, ndg, pow, ext
    // rep
    std::string inputstr;

    std::cout << "Available operations:" << std::endl
              << "No numbers: sig, rev, sum, del, shr, shl, mir, inv, sto" << std::endl
              << "One number: add, sub, mul, div, ndg, pow, ext" << std::endl
              << "Two numbers: rep" << std::endl
              << "Input style:" << std::endl
              << "beg;fin;mov;pin;pot;ops;op1_num11_num12;op2_num21_num22;op3_num31_num32;op4_num41_num42;op5_num51_num52;"
              << std::endl
              << ";;;;;;__;__;__;__;__;" << std::endl;

    std::cin >> inputstr;

    rules test(inputstr);
    test.calc();
    test.print();

    return 0;
}