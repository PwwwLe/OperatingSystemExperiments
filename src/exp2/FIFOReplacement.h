//
// Created by Sliver on 24-5-23.
//

#ifndef FIFO_H
#define FIFO_H

#include <queue>

#include "ReplacementAlgorithm.h"

using namespace std;

class FIFOReplacement : public ReplacementAlgorithm {
private:
      queue<int> replacementQueue;

public:
      int selectVictimFrame() override;
      void accessPage(int frameNumber) override;
};


#endif //FIFO_H
