//
// Created by chrisljiang on 2019-02-23.
//

#include <iostream>
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
    // sig, rev, sum, del, shr, shl, mir, inv, sto, add, sub, mul, div, ndg, pow, ext, rep

    moves.push_back(newmov);
    movrem--;

    std::string curop = newmov.specop;

    if (curop == "sig") { // change sign

        cur *= -1;

    } else if (curop == "rev") { // reverse

        std::string temp1 = int2str(cur), temp2;

        for (unsigned cnt = temp1.length() - 1; cnt >= 0; cnt--) {
            temp2 += temp1.at(cnt);
        }

        cur = str2int(temp2);

    } else if (curop == "sum") { // sum

        int temp = cur;
        cur = 0;
        bool neg = (temp < 0);

        if (neg) temp = abs(temp);

        while (temp > 0) {
            cur += temp % 10;
            temp /= 10;
        }

        if (neg) cur *= -1;

    } else if (curop == "del") { // delete

        cur /= 10;

    } else if (curop == "shr") { // shift right

        std::string temp = int2str(cur);
        temp = temp.substr(temp.length() - 1, std::string::npos) + temp.substr(0, temp.length() - 1);
        cur = str2int(temp);

    } else if (curop == "shl") { // shift left

        std::string temp = int2str(cur);
        temp = temp.substr(1, std::string::npos) + temp.substr(0, 1);
        cur = str2int(temp);

    } else if (curop == "mir") { // mirror

        std::string temp1 = int2str(cur), temp2 = temp1;

        for (unsigned cnt = temp1.length() - 1; cnt >= 0; cnt--) {
            temp2 += temp1.at(cnt);
        }

        cur = str2int(temp2);

    } else if (curop == "inv") { // invert

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

    } else if (curop == "sto") { // store

        cur = str2int(int2str(cur) + int2str(newmov.num1));

    } else if (curop == "add") { // add

        cur += newmov.num1 + extnum;

    } else if (curop == "sub") { // sub

        cur -= newmov.num1 + extnum;

    } else if (curop == "mul") { // multiply

        cur *= newmov.num1 + extnum;

    } else if (curop == "div") { // divide

        double temp = double(cur) / (newmov.num1 + extnum);
        cur /= newmov.num1 + extnum;
        temp -= cur;
        if (temp != 0) cur = INT_MAX;

    } else if (curop == "ndg") { // new digit

        cur = str2int(int2str(cur) + int2str(newmov.num1 + extnum));

    } else if (curop == "pow") { // power

        double temp = pow(cur, newmov.num1);
        cur = int(pow(cur, newmov.num1));
        temp -= cur;
        if (temp != 0) cur = INT_MAX;

    } else if (curop == "ext") { // extra

        extnum += newmov.num1;

    } else if (curop == "rep") { // replace

        std::vector<unsigned> locs;
        std::string nummain = int2str(cur);
        unsigned cnt = 0;

        while (cnt < nummain.length()) {
            cnt = nummain.find(newmov.str1, cnt);
            if (cnt != std::string::npos) {
                locs.push_back(cnt);
                cnt += newmov.str1.length();
            }
        }

        while (!locs.empty()) {
            unsigned loccur = locs.back();
            locs.pop_back();

            nummain.replace(loccur, newmov.str1.length(), newmov.str2);
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