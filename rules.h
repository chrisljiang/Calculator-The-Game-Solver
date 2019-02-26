//
// Created by chrisljiang on 2019-02-17.
//

#ifndef CALCULATORGAME_RULES_H
#define CALCULATORGAME_RULES_H

#include <vector>

#include "ops.h"
#include "sol.h"

class rules {
private:
    std::string initial;
    int beg, fin, movs, porin, porout, numOp;
    ops allops[5];
    std::vector<sol> sollst;
public:
    explicit rules(std::string initial);

    void calc();
    void print();
};

#endif //CALCULATORGAME_RULES_H