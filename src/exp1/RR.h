//
// Created by Sliver on 24-5-13.
//

#ifndef RR_H
#define RR_H

#include "PCB.h"
#include <vector>

using namespace std;

class RR {
private:
    vector<PCB> processes;
    int quantum;

public:
    RR(const vector<PCB>& processes, int q);

    vector<PCB> schedule();
};



#endif //RR_H
