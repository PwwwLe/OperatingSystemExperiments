//
// Created by Sliver on 24-5-13.
//

#include "RR.h"
#include <queue>

using namespace std;

RR::RR(const vector<PCB> &processes, int q) : processes(processes), quantum(q) {
}

vector<PCB> RR::schedule() {
    vector<PCB> readyQueue = processes;

    // 按照到达时间对序列排序
    sort(readyQueue.begin(), readyQueue.end(), [](const PCB& a, const PCB& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;
    // 结束队列
    vector<PCB> finishProcesses;

    while (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        readyQueue.erase(readyQueue.begin());

        // 计算执行时间
        int exeTime = min(currentProcess.getRemainingTime(), quantum);
        currentTime = max(currentTime, currentProcess.getArrivalTime());

        if (!currentProcess.isStartTimeSet()) {
            currentProcess.setStartTime(currentTime);
        }

        currentTime += exeTime;

        // 更新剩余时间
        currentProcess.setRemainingTime(currentProcess.getRemainingTime() - exeTime);

        if (currentProcess.getRemainingTime() > 0) {
            readyQueue.push_back(currentProcess);
        }else {
            currentProcess.setFinishTime(currentTime);
            currentProcess.setWaitingTime(
                currentProcess.getFinishTime() - currentProcess.getArrivalTime() - currentProcess.getBurstTime());
            currentProcess.setTurnaroundTime(currentProcess.getFinishTime() - currentProcess.getArrivalTime());
            finishProcesses.push_back(currentProcess);
        }
    }
    return finishProcesses;
}
