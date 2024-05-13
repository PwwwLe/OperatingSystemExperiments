//
// Created by Sliver on 24-5-9.
//

#ifndef PCB_H
#define PCB_H


enum ProcessState {
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};


class PCB {
private:
    int processID; // 进程ID
    ProcessState state; // 进程状态
    int priority; // 进程优先级
    int arrivalTime; // 进程到达时间
    int burstTime; // 进程运行时间
    int startTime = -1; // 进程开始执行的时间
    int finishTime; // 进程结束执行的时间
    int waitingTime; // 进程的等待时间
    int turnaroundTime; // 进程的周转时间
    int remainingTime; // 进程的剩余时间

public:
    // 构造函数
    PCB(int id, ProcessState st, int pri, int at, int bt);

    // 获取进程ID
    int getProcessID() const;

    // 获取进程状态
    ProcessState getState() const;

    // 设置进程状态
    void setState(ProcessState st);

    // 获取进程优先级
    int getPriority() const;

    // 获取进程到达时间
    int getArrivalTime() const;

    // 获取进程运行时间
    int getBurstTime() const;

    // 获取进程开始执行的时间
    int getStartTime() const;

    // 设置进程开始执行的时间
    void setStartTime(int time);

    bool isStartTimeSet() const;

    // 获取进程结束执行的时间
    int getFinishTime() const;

    // 设置进程结束执行的时间
    void setFinishTime(int time);

    // 获取进程的等待时间
    int getWaitingTime() const;

    // 设置进程的等待时间
    void setWaitingTime(int time);

    // 获取进程的周转时间
    int getTurnaroundTime() const;

    // 设置进程的周转时间
    void setTurnaroundTime(int time);

    // 获取进程的剩余时间
    int getRemainingTime() const;

    // 设置进程的剩余时间
    void setRemainingTime(int time);
};


#endif //PCB_H
