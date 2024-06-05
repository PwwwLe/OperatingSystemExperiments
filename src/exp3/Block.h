//
// Created by Sliver on 24-5-29.
//

#ifndef BLOCK_H
#define BLOCK_H

const int blockSize = 1024;
const int maxBlocks = 100;

class Block {
public:
    Block();


    char *data;
    int usedSize = 0;
};


#endif //BLOCK_H
