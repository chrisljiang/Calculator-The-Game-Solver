//
// Created by chrisljiang on 2019-02-23.
//

#include "extrafunc.h"

int str2int(std::string str) {
    int num = 0;
    bool neg = false;
    unsigned cnt = 0;

    if (str[0] == '-') {
        neg = true;
        cnt = 1;
    }

    for (; cnt < str.length(); cnt++) {
        num *= 10;
        num += str[cnt] - '0';
    }

    if (neg) num *= -1;

    return num;
}

std::string int2str(int num) {
    if (num == 0) return "0";

    int numcpy = abs(num);
    bool neg = (num < 0);
    std::string str;

    while (numcpy != 0) {
        char cur = char(numcpy % 10) + '0';
        numcpy /= 10;
        str = cur + str;
    }

    if (neg) str = '-' + str;

    return str;
}