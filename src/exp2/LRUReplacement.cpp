//
// Created by Sliver on 24-5-23.
//

#include "LRUReplacement.h"

int LRUReplacement::selectVictimFrame() {
    int victimFrame = accessList.front();
    accessList.pop_front();
    return victimFrame;
}

void LRUReplacement::accessPage(int frameNumber) {
    accessList.remove(frameNumber);
    accessList.push_back(frameNumber);
}


