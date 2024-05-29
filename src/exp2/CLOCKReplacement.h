//
// Created by Sliver on 24-5-23.
//

#ifndef CLOCK_H
#define CLOCK_H
#include <vector>

#include "ReplacementAlgorithm.h"
#include "VirtualMemoryManager.h"

using namespace std;

class CLOCKReplacement : public ReplacementAlgorithm {
private:
    vector<Page>& physicalMemory;
    int clockHand;
    void advanceClockHand();
public:
    CLOCKReplacement(vector<Page>& physicalMemory);
    int selectVictimFrame() override;
    void accessPage(int frameNumber) override;
};



#endif //CLOCK_H
