//
// Created by Sliver on 24-5-9.
//

#include "SJF.h"
#include "PerformanceMetrics.h"
#include <algorithm>
#include <iostream>

using namespace std;

SJF::SJF(vector<PCB> proc) : processes(proc) {
}

vector<PCB> SJF::schedule() {
    vector<PCB> processQueue = processes;

    // 按照到达时间对序列进行排序
    sort(processQueue.begin(), processQueue.end(), [](const PCB &a, const PCB &b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;

    // 就绪队列
    vector<PCB> readyQueue;

    // 结束队列
    vector<PCB> finishedProcesses;

    while (!processQueue.empty() || !readyQueue.empty()) {
        // 到达的进程加入就绪队列
        while (!processQueue.empty() && processQueue.front().getArrivalTime() <= currentTime) {
            readyQueue.push_back(processQueue.front());
            processQueue.erase(processQueue.begin());
        }

        // 将就绪队列按照执行时间排序
        sort(readyQueue.begin(), readyQueue.end(), [](const PCB &a, const PCB &b) {
            return a.getBurstTime() < b.getBurstTime();
        });

        if (!readyQueue.empty()) {
            // 模拟进程执行
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
