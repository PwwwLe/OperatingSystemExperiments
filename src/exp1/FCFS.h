#ifndef FCFS_H
#define FCFS_H

#include "PCB.h"
#include <vector>

using namespace std;

class FCFS {
private:
    vector<PCB> processes;

public:
    FCFS(vector<PCB> proc);
    vector<PCB> schedule();
};

#endif // FCFS_H
