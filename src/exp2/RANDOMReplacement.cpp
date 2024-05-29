//
// Created by Sliver on 24-5-23.
//

#include "RANDOMReplacement.h"

#include <cstdlib>
#include <ctime>
#include <iostream>


RANDOMReplacement::RANDOMReplacement(int numPages) {
    cout << "RANDOMReplacement initialized with numPages: " << numPages << endl;
    srand(time(nullptr));
    this->numPages = numPages;
}

int RANDOMReplacement::selectVictimFrame() {
    int victim = rand() % numPages;
    cout << "Selected victim frame: " << victim << " out of " << numPages << " pages" << endl;
    return victim;
}

void RANDOMReplacement::accessPage(int frameNumber) {
}

