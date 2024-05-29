//
// Created by Sliver on 24-5-23.
//

#ifndef RANDOM_H
#define RANDOM_H

#include "ReplacementAlgorithm.h"

using namespace std;

class RANDOMReplacement : public ReplacementAlgorithm{
private:
    int numPages;
public:
    RANDOMReplacement(int numPages);
    int selectVictimFrame() override;
    void accessPage(int frameNumber) override;
};



#endif //RANDOM_H
