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

int PCB::getProcessID() const {
    return processID;
}

ProcessState PCB::getState() const {
    return state;
}

void PCB::setState(ProcessState st) {
    state = st;
}

int PCB::getPriority() const {
    return priority;
}

int PCB::getArrivalTime() const {
    return arrivalTime;
}

int PCB::getBurstTime() const {
    return burstTime;
}

int PCB::getStartTime() const {
    return startTime;
}

bool PCB::isStartTimeSet() const {
    return startTime != -1;
}

void PCB::setStartTime(int time) {
    if (startTime == -1) startTime = time;
}

int PCB::getFinishTime() const {
    return finishTime;
}

void PCB::setFinishTime(int time) {
    finishTime = time;
}

int PCB::getWaitingTime() const {
    return waitingTime;
}

void PCB::setWaitingTime(int time) {
    waitingTime = time;
}

int PCB::getTurnaroundTime() const {
    return turnaroundTime;
}

void PCB::setTurnaroundTime(int time) {
    turnaroundTime = time;
}

int PCB::getRemainingTime() const {
    return remainingTime;
}

void PCB::setRemainingTime(int time) {
    remainingTime = time;
}
