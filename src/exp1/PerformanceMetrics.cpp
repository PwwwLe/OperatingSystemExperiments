//
// Created by Sliver on 24-5-9.
//

#include "PerformanceMetrics.h"

using namespace std;

// 计算平均周转时间
double calculateAverageTurnaroundTime(const vector<PCB>& processes) {
    double totalTurnaroundTime = 0;
    for (const PCB& process : processes) {
        totalTurnaroundTime += process.getFinishTime() - process.getArrivalTime();
    }
    return totalTurnaroundTime / processes.size();
}

// 计算平均带权周转时间
double calculateAverageWeightedTurnaroundTime(const vector<PCB>& processes) {
    double totalWeightedTurnaroundTime = 0;
    for (const PCB& process : processes) {
        totalWeightedTurnaroundTime += (process.getFinishTime() - process.getArrivalTime()) / (double)process.getBurstTime();
    }
    return totalWeightedTurnaroundTime / processes.size();
}

// 计算平均等待时间
double calculateAverageWaitingTime(const vector<PCB>& processes) {
    double totalWaitingTime = 0;
    for (const PCB& process : processes) {
        totalWaitingTime += process.getStartTime() - process.getArrivalTime();
    }
    return totalWaitingTime / processes.size();
}
