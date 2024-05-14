//
// Created by Sliver on 24-5-13.
//

#ifndef MLFQ_H
#define MLFQ_H
#include <vector>
#include "PCB.h"

using namespace std;

struct prioQueue {
    int quantum;
    vector<PCB> processes;
};

class MLFQ {
private:
    int num;                    // 优先级队列数
    vector<prioQueue> queues;   // 优先级队列
    vector<int> quantums;       // 每个队列的时间片大小

public:
    MLFQ(int n,vector<PCB>& processes, vector<int> q);

    vector<PCB> schedule();
};



#endif //MLFQ_H
