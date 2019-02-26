//
// Created by chrisljiang on 2019-02-23.
//

#ifndef CALCULATORGAME_SOL_H
#define CALCULATORGAME_SOL_H

#include <vector>

#include "ops.h"

struct sol {
    int cur, movrem, extnum, porin, porout;
    std::vector<ops> moves;
    std::vector<int> pstval;

    sol(int cur, int movrem, int porin, int porout);
    void add(ops newmov);
};

#endif //CALCULATORGAME_SOL_H