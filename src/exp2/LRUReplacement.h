//
// Created by Sliver on 24-5-23.
//

#ifndef LRU_H
#define LRU_H
#include "ReplacementAlgorithm.h"
#include <list>

using namespace std;

class LRUReplacement : public ReplacementAlgorithm{
private:
    list<int> accessList;

public:
    int selectVictimFrame() override;
    void accessPage(int frameNumber) override;
};



#endif //LRU_H
