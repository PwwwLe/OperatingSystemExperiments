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
    int processID;
    ProcessState state;
    int priority;
    int arrivalTime;
    int burstTime;
    int startTime = -1;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;

public:
    PCB(int id, ProcessState st, int pri, int at, int bt);

    int getProcessID() const;

    ProcessState getState() const;

    void setState(ProcessState st);

    int getPriority() const;

    int getArrivalTime() const;

    int getBurstTime() const;

    int getStartTime() const;

    void setStartTime(int time);

    bool isStartTimeSet() const;

    int getFinishTime() const;

    void setFinishTime(int time);

    int getWaitingTime() const;

    void setWaitingTime(int time);

    int getTurnaroundTime() const;

    void setTurnaroundTime(int time);

    int getRemainingTime() const;

    void setRemainingTime(int time);
};


#endif //PCB_H
