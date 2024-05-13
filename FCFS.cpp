//
// Created by Sliver on 24-5-9.
//

#include "FCFS.h"
#include "PerformanceMetrics.h"
#include <queue>
#include <algorithm>

using namespace std;

FCFS::FCFS(vector<PCB> proc) : processes(proc) {
}

vector<PCB> FCFS::schedule() {
    vector<PCB> readyQueue;
    sort(readyQueue.begin(), readyQueue.end(), [] (const PCB &p1, const PCB &p2){
        return p1.getArrivalTime() > p2.getArrivalTime();
    });
    vector<PCB> finishedProcesses;

    for (const PCB &process: processes) {
        readyQueue.push_back(process);
    }

    int currentTime = 0;

    while (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        readyQueue.erase(readyQueue.begin());

        currentProcess.setStartTime(max(currentTime, currentProcess.getArrivalTime()));
        currentTime = currentProcess.getStartTime() + currentProcess.getBurstTime();

        currentProcess.setFinishTime(currentTime);
        currentProcess.setWaitingTime(
                currentProcess.getFinishTime() - currentProcess.getArrivalTime() - currentProcess.getBurstTime());
        currentProcess.setTurnaroundTime(currentProcess.getFinishTime() - currentProcess.getArrivalTime());
        finishedProcesses.push_back(currentProcess);
    }
    return finishedProcesses;
}

