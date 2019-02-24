//
// Created by chrisljiang on 2019-02-23.
//

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cmath>

#include "sol.h"
#include "extrafunc.h"

sol::sol(int cur, int movrem, int porin, int porout) {
    this->cur = cur;
    this->movrem = movrem;
    this->porin = porin;
    this->porout = porout;
    extnum = 0;
    pstval.push_back(cur);
}

void sol::add(ops newmov) {
    // none, sign, reverse, sum, del, shiftr, shiftl, mirror, inv, store
    // add, subtract, multiply, divide, newdig, power, extra
    // replace

    moves.push_back(newmov);
    movrem--;

    std::string curop = newmov.specop;

    if (curop == "sign") {

        cur *= -1;

    } else if (curop == "reverse") {

        std::string temp1 = int2str(cur), temp2;

        for (int cnt = temp1.length() - 1; cnt >= 0; cnt--) {
            temp2 += temp1.at(cnt);
        }

        cur = str2int(temp2);

    } else if (curop == "sum") {

        int temp = cur;
        cur = 0;
        bool neg = (temp < 0);

        if (neg) temp = abs(temp);

        while (temp > 0) {
            cur += temp % 10;
            temp /= 10;
        }

        if (neg) cur *= -1;

    } else if (curop == "del") {

        cur /= 10;

    } else if (curop == "shiftr") {

        std::string temp = int2str(cur);
        temp = temp.substr(temp.length() - 1, std::string::npos) + temp.substr(0, temp.length() - 1);
        cur = str2int(temp);

    } else if (curop == "shiftl") {

        std::string temp = int2str(cur);
        temp = temp.substr(1, std::string::npos) + temp.substr(0, 1);
        cur = str2int(temp);

    } else if (curop == "mirror") {

        std::string temp1 = int2str(cur), temp2 = temp1;

        for (int cnt = temp1.length() - 1; cnt >= 0; cnt--) {
            temp2 += temp1.at(cnt);
        }

        cur = str2int(temp2);

    } else if (curop == "inv") {

        std::string temp = int2str(cur);

        for (unsigned cnt = 0; cnt < temp.length(); cnt++) {
            char cur = temp.at(cnt);

            if (cur == '1') {
                cur = '9';
            } else if (cur == '2') {
                cur = '8';
            } else if (cur == '3') {
                cur = '7';
            } else if (cur == '4') {
                cur = '6';
            } else if (cur == '6') {
                cur = '4';
            } else if (cur == '7') {
                cur = '3';
            } else if (cur == '8') {
                cur = '2';
            } else if (cur == '9') {
                cur = '1';
            }

            temp.at(cnt) = cur;
        }

        cur = str2int(temp);

    } else if (curop == "store") {

        cur = str2int(int2str(cur) + int2str(newmov.num1));

    } else if (curop == "add") {

        cur += newmov.num1 + extnum;

    } else if (curop == "subtract") {

        cur -= newmov.num1 + extnum;

    } else if (curop == "multiply") {

        cur *= newmov.num1 + extnum;

    } else if (curop == "divide") {

        double temp = double(cur) / (newmov.num1 + extnum);
        cur /= newmov.num1 + extnum;
        temp -= cur;
        if (temp != 0) cur = INT_MAX;

    } else if (curop == "newdig") {

        cur = str2int(int2str(cur) + int2str(newmov.num1 + extnum));

    } else if (curop == "power") {

        double temp = pow(cur, newmov.num1);
        cur = pow(cur, newmov.num1);
        temp -= cur;
        if (temp != 0) cur = INT_MAX;

    } else if (curop == "extra") {

        extnum += newmov.num1;

    } else if (curop == "replace") {

        std::vector<unsigned> locs;
        std::string num1str = newmov.str1, num2str = newmov.str2, nummain = int2str(cur);
        //int2str(newmov.num1), num2str = int2str(newmov.num2), nummain = int2str(cur);
        unsigned cnt = 0;

        while (cnt < nummain.length()) {
            cnt = nummain.find(num1str, cnt);
            if (cnt != std::string::npos) {
                locs.push_back(cnt);
                cnt += num1str.length();
            }
        }

        while (!locs.empty()) {
            unsigned loccur = locs.back();
            locs.pop_back();

            nummain.replace(loccur, num1str.length(), num2str);
        }

        cur = str2int(nummain);

    } else {

        std::cout << "Op not found" << std::endl;
        cur = INT_MAX;

    }

    int pormov = cur / porin;

    while (pormov) {
        cur = cur - ((cur / porin) * porin) + (((cur / porin) - ((cur / porin) % 10)) * (porin / 10));
        cur += (pormov % 10) * porout;
        pormov = cur / porin;
    }

    pstval.push_back(cur);
}