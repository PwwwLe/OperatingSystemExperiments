//
// Created by Sliver on 24-5-23.
//

#include "CLOCKReplacement.h"

CLOCKReplacement::CLOCKReplacement(vector<Page> &physicalMemory) : physicalMemory(physicalMemory), clockHand(0) {
}


int CLOCKReplacement::selectVictimFrame() {
    while (true) {
        Page &currentPage = physicalMemory[clockHand];

        if (!currentPage.referenced) {
            int victimFrame = clockHand;
            advanceClockHand();
            return victimFrame;
        } else {
            currentPage.referenced = false;
            advanceClockHand();
        }
    }
}

void CLOCKReplacement::accessPage(int frameNumber) {
    physicalMemory[frameNumber].referenced = true;
}

void CLOCKReplacement::advanceClockHand() {
    clockHand = (clockHand + 1) % physicalMemory.size();
}


