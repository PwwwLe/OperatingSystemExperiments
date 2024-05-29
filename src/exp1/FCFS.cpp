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
    // 就绪队列
    vector<PCB> readyQueue = processes;

    // 按照到达时间顺序对就绪队列排序
    sort(readyQueue.begin(), readyQueue.end(), [] (const PCB &p1, const PCB &p2){
        return p1.getArrivalTime() < p2.getArrivalTime();
    });

    // 结束进程数组
    vector<PCB> finishedProcesses;

    int currentTime = 0;

    while (!readyQueue.empty()) {
        PCB currentProcess = readyQueue.front();
        readyQueue.erase(readyQueue.begin());

        // 设置开始时间
        currentProcess.setStartTime(max(currentTime, currentProcess.getArrivalTime()));
        currentTime = currentProcess.getStartTime() + currentProcess.getBurstTime();

        // 设置结束时间、等待时间、周转时间，并将执行完的进程加入结束进程中
        currentProcess.setFinishTime(currentTime);
        currentProcess.setWaitingTime(
                currentProcess.getFinishTime() - currentProcess.getArrivalTime() - currentProcess.getBurstTime());
        currentProcess.setTurnaroundTime(currentProcess.getFinishTime() - currentProcess.getArrivalTime());
        finishedProcesses.push_back(currentProcess);
    }
    return finishedProcesses;
}

