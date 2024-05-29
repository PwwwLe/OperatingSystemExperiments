//
// Created by Sliver on 24-5-23.
//

#ifndef VIRTUALMEMORYMANAGER_H
#define VIRTUALMEMORYMANAGER_H
#include <vector>

#include "ReplacementAlgorithm.h"

using namespace std;

struct Page {
    int pageNumber;
    bool valid;
    bool referenced;
    Page() : pageNumber(-1), valid(false), referenced(false) {}
};

struct PageTableEntry {
    int frameNumber;
    bool valid;
    PageTableEntry() : frameNumber(-1), valid(false) {}
};

enum ReplacementPolicy {
    FIFO,
    LRU,
    CLOCK,
    RANDOM
};

class VirtualMemoryManager {
private:
    int pageFaults;
    int totalPageAccesses;
    double totalAccessTime;
    int pageSize;

    ReplacementPolicy policy;
    ReplacementAlgorithm* replacementAlgorithm;
    vector<PageTableEntry> pageTable;
    vector<Page> physicalMemory;
    void handlePageFault(int virtualPageNumber);
    bool isPhysicalMemoryFull();
    int findEmptyFrame();
    void loadPageToFrame(int virtualPageNumber, int frameNumber);

public:
    VirtualMemoryManager(ReplacementPolicy policy, int numPages, int numVirtualPages, int pageSize);
    void accessPage(int virtualPageNumber);
    void printPageTable();
    void printPerformanceMetrics();
    void printPhysicalMemory();
    int translateVirtualAddress(int virtualAddress);
    int translatePhysicalAddress(int physicalAddress);
    void setReplacementPolicy(ReplacementPolicy policy);

};



#endif //VIRTUALMEMORYMANAGER_H
