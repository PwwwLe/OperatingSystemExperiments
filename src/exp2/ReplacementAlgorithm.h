//
// Created by Sliver on 24-5-23.
//

#ifndef REPLACEMENTALGORITHM_H
#define REPLACEMENTALGORITHM_H



class ReplacementAlgorithm {
public:
    virtual ~ReplacementAlgorithm() = default;
    virtual int selectVictimFrame() = 0;
    virtual void accessPage(int frameNumber) = 0;
};



#endif //REPLACEMENTALGORITHM_H
