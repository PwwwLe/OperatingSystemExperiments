//
// Created by Sliver on 24-5-13.
//

#include "MLFQ.h"

using namespace std;


MLFQ::MLFQ(int n, vector<PCB> &processes, vector<int> qs) {
    // 新建n个优先级队列
    queues.resize(n);
    for (int i = 0; i < n; ++i) {
        queues[i].quantum = qs[i];
    }

    // 按到达时间排序
    sort(processes.begin(), processes.end(), [](const PCB &p1, const PCB &p2) {
        return p1.getArrivalTime() < p2.getArrivalTime();
    });

    // 将进程添加到待处理进程队列
    pendingProcesses = processes;
}

vector<PCB> MLFQ::schedule() {
    int currentTime = 0;
    vector<PCB> finishProcesses;

    // 执行调度
    while (true) {
        bool isAllEmpty = true;

        if (!pendingProcesses.empty()) {
            currentTime = max(currentTime, pendingProcesses.front().getArrivalTime());
            while (!pendingProcesses.empty() && pendingProcesses.front().getArrivalTime() <= currentTime) {
                queues[0].processes.push_back(pendingProcesses.front());
                pendingProcesses.erase(pendingProcesses.begin());
            }
        }

        // 迭代执行每个优先级队列
        for (int i = 0; i < queues.size(); ++i) {
            // 当前的优先级队列
            auto &queue = queues[i];

            // 执行当前优先级队列的所有进程
            while (!queue.processes.empty()) {
                isAllEmpty = false;
                PCB currentProcess = queue.processes.front();
                queue.processes.erase(queue.processes.begin());

                // 计算执行时间
                int executionTime = min(queue.quantum, currentProcess.getBurstTime());
                currentTime = max(currentTime, currentProcess.getArrivalTime());

                if (!currentProcess.isStartTimeSet()) {
                    currentProcess.setStartTime(currentTime);
                }

                currentTime += executionTime;
                // 更新剩余时间
                currentProcess.setRemainingTime(currentProcess.getRemainingTime() - executionTime);

                // 检查进程是否执行完成
                if (currentProcess.getRemainingTime() > 0) {
                    if (i < queues.size() - 1) {
                        // 将进程添加到下一级优先级队列
                        queues[i + 1].processes.push_back(currentProcess);
                    } else {
                        queue.processes.push_back(currentProcess);
                    }
                } else {
                    currentProcess.setFinishTime(currentTime);
                    currentProcess.setWaitingTime(
                        currentProcess.getFinishTime() - currentProcess.getArrivalTime() - currentProcess.
                        getBurstTime());
                    currentProcess.setTurnaroundTime(currentProcess.getFinishTime() - currentProcess.getArrivalTime());
                    finishProcesses.push_back(currentProcess);
                }

                // 检查是否有新进程到达，并添加到优先级最高的队列
                while (!pendingProcesses.empty() && pendingProcesses.front().getArrivalTime() <= currentTime) {
                    queues[0].processes.push_back(pendingProcesses.front());
                    pendingProcesses.erase(pendingProcesses.begin());
                }
            }
        }

        // 如果优先级队列全空，则跳出循环
        if (isAllEmpty && pendingProcesses.empty()) {
            break;
        }
    }
    return finishProcesses;
}
