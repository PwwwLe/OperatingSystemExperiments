//
// Created by Sliver on 24-5-9.
//

#ifndef PERFORMANCEMATRICS_H
#define PERFORMANCEMATRICS_H

#include "PCB.h"
#include <vector>

using namespace std;

// 计算平均周转时间
double calculateAverageTurnaroundTime(const vector<PCB>& processes);

// 计算平均带权周转时间
double calculateAverageWeightedTurnaroundTime(const vector<PCB>& processes);

// 计算平均等待时间
double calculateAverageWaitingTime(const vector<PCB>& processes);

#endif //PERFORMANCEMATRICS_H
