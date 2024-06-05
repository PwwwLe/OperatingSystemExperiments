//
// Created by Sliver on 24-5-29.
//

#include "Block.h"
#include <algorithm>

using namespace std;

Block::Block() {
    data = new char[blockSize];
    fill(data, data + blockSize, '\0');
}



