//
// Created by Sliver on 24-5-23.
//

#include "FIFOReplacement.h"

int FIFOReplacement::selectVictimFrame() {
    int victimFrame = replacementQueue.front();
    replacementQueue.pop();
    return victimFrame;
}

void FIFOReplacement::accessPage(int frameNumber) {
    replacementQueue.push(frameNumber);
}

