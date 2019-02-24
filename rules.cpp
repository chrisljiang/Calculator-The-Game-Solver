//
// Created by chrisljiang on 2019-02-17.
//

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

#include "rules.h"
#include "ops.h"
#include "sol.h"
#include "extrafunc.h"

rules::rules(std::string initial) {
    // beg;fin;movs;porin;porout;numOp;op1_num11_num12;op2_num21_num22;op3_num31_num32;op4_num41_num42;op5_num51_num52;

    this->initial = initial;

    unsigned loc = 0, nex = initial.find(';', loc);

    beg = str2int(initial.substr(loc, nex - loc));
    loc = nex + 1;
    nex = initial.find(';', loc);
    fin = str2int(initial.substr(loc, nex - loc));
    loc = nex + 1;
    nex = initial.find(';', loc);
    movs = str2int(initial.substr(loc, nex - loc));
    loc = nex + 1;
    nex = initial.find(';', loc);
    porin = str2int(initial.substr(loc, nex - loc));
    loc = nex + 1;
    nex = initial.find(';', loc);
    porout = str2int(initial.substr(loc, nex - loc));
    loc = nex + 1;
    nex = initial.find(';', loc);
    numOp = str2int(initial.substr(loc, nex - loc));

    for (unsigned cnt = 0; cnt < numOp; cnt++) {
        loc = nex + 1;
        nex = initial.find(';', loc);
        unsigned mid1 = initial.find('_', loc), mid2 = initial.find('_', mid1 + 1);

        allops[cnt].specop = initial.substr(loc, mid1 - loc);
        if (mid2 - mid1 != 1) {
            allops[cnt].str1 = initial.substr(mid1 + 1, mid2 - mid1 -1);
            allops[cnt].num1 = str2int(allops[cnt].str1);

            if (nex - mid2 != 1) {
                allops[cnt].str2 = initial.substr(mid2 + 1, nex - mid2 -1);
                allops[cnt].num2 = str2int(allops[cnt].str2);
            }
        }
    }

    if (porin != porout) {
        int temp = porin;
        porin = 1;
        for (int cnt = 0; cnt < temp; cnt++) {
            porin *= 10;
        }

        temp = porout;
        porout = 1;
        for (int cnt = 0; cnt < temp; cnt++) {
            porout *= 10;
        }
    } else {
        porin = 1000000;
        porout = 1;
    }
}

void rules::calc() {
    std::queue<sol> solpos;
    solpos.push(sol(beg, movs, porin, porout));

    while (!solpos.empty()) {
        sol solcur = solpos.front();
        solpos.pop();

        for (unsigned cnt = 0; cnt < numOp; cnt++) {
            sol solnxt = solcur;
            if (allops[cnt].specop != "store") {
                solnxt.add(allops[cnt]);

                if (solnxt.cur == fin) sollst.push_back(solnxt);
                else if (solnxt.movrem > 0 && solnxt.cur != INT_MAX && abs(solnxt.cur) <= 999999) solpos.push(solnxt);
            } else {
                std::vector<int> psttmp = solnxt.pstval;
                while (!psttmp.empty()) {
                    sol soltmp = solnxt;
                    ops optmp = allops[cnt];
                    optmp.num1 = psttmp.at(0);

                    soltmp.add(optmp);
                    soltmp.pstval = psttmp;
                    soltmp.pstval.push_back(soltmp.cur);
                    psttmp.erase(psttmp.begin());

                    if (soltmp.cur == fin) sollst.push_back(soltmp);
                    else if (soltmp.movrem > 0 && soltmp.cur != INT_MAX && abs(soltmp.cur) <= 999999)
                        solpos.push(soltmp);
                }
            }


        }
    }
}

void rules::print() {
    std::cout << "beg\tfin\tmovs\tporin\tporout\tnumOp" << std::endl
              << beg << "\t"
              << fin << "\t"
              << movs << "\t"
              << porin << "\t"
              << porout << "\t"
              << numOp << std::endl << std::endl;


    for (unsigned cnt = 0; cnt < numOp; cnt++) {
        std::cout << allops[cnt].specop << "\t" << allops[cnt].num1 << "\t" << allops[cnt].num2 << std::endl;
    }

    std::cout << std::endl;

    for (std::vector<sol>::iterator it = sollst.begin(); it != sollst.end(); ++it) {
        for (std::vector<ops>::iterator cur = it->moves.begin(); cur != it->moves.end(); ++cur) {
            std::cout << cur->specop;


            // none, sign, reverse, sum, del, shiftr, shiftl, mirror, store
            // add, subtract, multiply, divide, newdig, power, extra
            // replace

            if (cur->specop == "store" ||
                cur->specop == "add" ||
                cur->specop == "subtract" ||
                cur->specop == "multiply" ||
                cur->specop == "divide" ||
                cur->specop == "newdig" ||
                cur->specop == "power" ||
                cur->specop == "extra" ||
                cur->specop == "replace") {

                std::cout << "-" << cur->num1;

                if (cur->specop == "replace") std::cout << "-" << cur->num2;
            }

            std::cout << "\t";
        }

        std::cout << std::endl;
    }
}