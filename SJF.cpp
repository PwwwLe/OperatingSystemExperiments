//
// Created by Sliver on 24-5-9.
//

#include "SJF.h"
#include "PerformanceMetrics.h"
#include <algorithm>
#include <iostream>

using namespace std;

// 按到达时间排序
bool sortByArrivalTime(const PCB &a, const PCB &b) {
    return a.getArrivalTime() < b.getArrivalTime();
}

// 按运行时间排序
bool sortByBurstTime(const PCB &a, const PCB &b) {
    return a.getBurstTime() < b.getBurstTime();
}

SJF::SJF(vector<PCB> proc) : processes(proc) {
}

vector<PCB> SJF::schedule() {
    vector<PCB> processQueue = processes;

    sort(processQueue.begin(), processQueue.end(), sortByArrivalTime);

    int currentTime = 0;

    vector<PCB> readyQueue;

    vector<PCB> finishedProcesses;

    while (!processQueue.empty() || !readyQueue.empty()) {
        while (!processQueue.empty() && processQueue.front().getArrivalTime() <= currentTime) {
            readyQueue.push_back(processQueue.front());
            processQueue.erase(processQueue.begin());
        }

        sort(readyQueue.begin(), readyQueue.end(), sortByBurstTime);

        if (!readyQueue.empty()) {
            PCB currentProcess = readyQueue.front();
            readyQueue.erase(readyQueue.begin());

            currentProcess.setStartTime(currentTime);

            currentTime += currentProcess.getBurstTime();

            currentProcess.setFinishTime(currentTime);
            currentProcess.setWaitingTime(
                currentProcess.getFinishTime() - currentProcess.getArrivalTime() - currentProcess.getBurstTime());
            currentProcess.setTurnaroundTime(currentProcess.getFinishTime() - currentProcess.getArrivalTime());
            finishedProcesses.push_back(currentProcess);
        } else {
            currentTime = processQueue.front().getArrivalTime();
        }
    }

    return finishedProcesses;
}
