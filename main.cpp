#include "PCB.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
#include "MLFQ.h"
#include "PerformanceMetrics.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Function to print the header for process information
void printProcessHeader() {
    cout << left
            << setw(15) << "Process ID"
            << setw(15) << "Arrival Time"
            << setw(15) << "Burst Time"
            << setw(15) << "Start Time"
            << setw(15) << "Finish Time"
            << setw(15) << "Waiting Time"
            << endl;
    cout << setfill('-') << setw(90) << "-" << endl;
    cout << setfill(' ');
}

// Function to print each process information
void printProcessInfo(const PCB &process) {
    cout << left
            << setw(15) << process.getProcessID()
            << setw(15) << process.getArrivalTime()
            << setw(15) << process.getBurstTime()
            << setw(15) << process.getStartTime()
            << setw(15) << process.getFinishTime()
            << setw(15) << process.getWaitingTime()
            << endl;
}

// Function to print performance metrics
void display(const vector<PCB> &processes) {
    printProcessHeader();
    for (const PCB &process: processes) {
        printProcessInfo(process);
    }

    cout << "\nPerformance Metrics:" << endl;
    cout << "Average Turnaround Time: " << calculateAverageTurnaroundTime(processes) << endl;
    cout << "Average Weighted Turnaround Time: " << calculateAverageWeightedTurnaroundTime(processes) << endl;
    cout << "Average Waiting Time: " << calculateAverageWaitingTime(processes) << endl;
    cout << endl;
    cout << endl;
}


// 生成随机测试数据集函数
vector<PCB> generateTestData(int numProcesses) {
    vector<PCB> processes;
    srand(time(nullptr)); // 设置随机种子

    for (int i = 0; i < numProcesses; ++i) {
        // 生成随机的到达时间、运行时间和优先级
        int arrivalTime = rand() % 20; // 到达时间在0到19之间随机
        int burstTime = rand() % 10 + 1; // 运行时间在1到10之间随机
        int priority = rand() % 5 + 1; // 优先级在1到5之间随机

        PCB process(i + 1, READY, priority, arrivalTime, burstTime); // 进程ID从1开始编号
        processes.push_back(process);
    }

    return processes;
}

int main() {
    int numProcesses = 10; // Example number of processes
    vector<PCB> testData = generateTestData(numProcesses);

    cout << "Initial Processes: " << endl;

    printProcessHeader();
    for (const PCB &process: testData) {
        printProcessInfo(process);
    }

    cout << endl;
    cout << endl;

    cout << "FCFS Algorithms: " << endl;
    FCFS fcfsScheduler(testData);
    vector<PCB> fcfsFinishedProcesses = fcfsScheduler.schedule();
    display(fcfsFinishedProcesses);

    cout << "SJF Algorithms: " << endl;
    SJF sjfScheduler(testData);
    vector<PCB> sjfFinishedProcesse = sjfScheduler.schedule();
    display(sjfFinishedProcesse);

    cout << "RR Algorithms: " << endl;
    RR rrScheduler(testData, 5);
    vector<PCB> rrFinishedProcesses = rrScheduler.schedule();
    display(rrFinishedProcesses);

    cout << "MLFQ Algorithms: " << endl;
    vector<int> quantums = {2, 4, 6};
    MLFQ mlfqScheduler(3, testData, quantums);
    vector<PCB> mlfqFinishedProcesses = mlfqScheduler.schedule();
    display(mlfqFinishedProcesses);

    return 0;
}
