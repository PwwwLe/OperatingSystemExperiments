//
// Created by Sliver on 24-5-9.
//

#include "PCB.h"
#include <iostream>

using namespace std;

PCB::PCB(int id, ProcessState st, int pri, int at, int bt) : processID(id), state(st), priority(pri),
                                                             arrivalTime(at), burstTime(bt),
                                                             finishTime(0), waitingTime(0),
                                                             turnaroundTime(0), remainingTime(bt) {
}

// 获取进程ID
int PCB::getProcessID() const {
    return processID;
}

// 获取进程状态
ProcessState PCB::getState() const {
    return state;
}

// 设置进程状态
void PCB::setState(ProcessState st) {
    state = st;
}

// 获取进程优先级
int PCB::getPriority() const {
    return priority;
}

// 获取进程到达时间
int PCB::getArrivalTime() const {
    return arrivalTime;
}

// 获取进程运行时间
int PCB::getBurstTime() const {
    return burstTime;
}

// 获取进程开始执行的时间
int PCB::getStartTime() const {
    return startTime;
}

bool PCB::isStartTimeSet() const {
    return startTime != -1;
}

// 设置进程开始执行的时间
void PCB::setStartTime(int time) {
    if (startTime == -1) startTime = time;
}

// 获取进程结束执行的时间
int PCB::getFinishTime() const {
    return finishTime;
}

// 设置进程结束执行的时间
void PCB::setFinishTime(int time) {
    finishTime = time;
}

// 获取进程的等待时间
int PCB::getWaitingTime() const {
    return waitingTime;
}

// 设置进程的等待时间
void PCB::setWaitingTime(int time) {
    waitingTime = time;
}

// 获取进程的周转时间
int PCB::getTurnaroundTime() const {
    return turnaroundTime;
}

// 设置进程的周转时间
void PCB::setTurnaroundTime(int time) {
    turnaroundTime = time;
}

// 获取进程的剩余时间
int PCB::getRemainingTime() const {
    return remainingTime;
}

// 设置进程的剩余时间
void PCB::setRemainingTime(int time) {
    remainingTime = time;
}
