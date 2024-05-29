//
// Created by Sliver on 24-5-9.
//

#ifndef SJF_H
#define SJF_H

#include "PCB.h"
#include <vector>

using namespace std;

class SJF {
private:
    vector<PCB> processes;

public:
    SJF(vector<PCB> proc);

    vector<PCB> schedule();

};

#endif //SJF_H
