//
// Created by Sliver on 24-5-23.
//

#include "VirtualMemoryManager.h"

#include <iostream>
#include <iomanip>

#include "CLOCKReplacement.h"
#include "FIFOReplacement.h"
#include "LRUReplacement.h"
#include "RANDOMReplacement.h"

VirtualMemoryManager::VirtualMemoryManager(ReplacementPolicy policy, int numPages, int numVirtualPages,
                                           int pageSize) : policy(policy), pageFaults(0), totalPageAccesses(0),
                                                           totalAccessTime(0.0), pageSize(pageSize) {
    pageTable = vector<PageTableEntry>(numVirtualPages);
    physicalMemory = vector<Page>(numPages);

    setReplacementPolicy(policy);
}

void VirtualMemoryManager::setReplacementPolicy(ReplacementPolicy policy) {
    delete replacementAlgorithm;
    switch (policy) {
        case FIFO:
            replacementAlgorithm = new FIFOReplacement();
            break;
        case LRU:
            replacementAlgorithm = new LRUReplacement();
            break;
        case CLOCK:
            replacementAlgorithm = new CLOCKReplacement(physicalMemory);
            break;
        case RANDOM:
            replacementAlgorithm = new RANDOMReplacement(physicalMemory.size());
        break;
    }
}

void VirtualMemoryManager::accessPage(int virtualPageNumber) {
    totalPageAccesses++;

    PageTableEntry& pte = pageTable[virtualPageNumber];
    if (pte.valid) {
        cout << "Page " << virtualPageNumber << " is already in the memory. Frame: " << pte.frameNumber << endl;
        replacementAlgorithm->accessPage(pte.frameNumber);
    }else {
        cout << "Page " << virtualPageNumber << " is not in the memory." << endl;
        handlePageFault(virtualPageNumber);
        pageFaults++;
    }
}

void VirtualMemoryManager::handlePageFault(int virtualPageNumber) {
    int frameNumber;
    if (isPhysicalMemoryFull()) {
        frameNumber = replacementAlgorithm->selectVictimFrame();
        for (int i = 0; i < pageTable.size(); ++i) {
            if (pageTable[i].frameNumber == frameNumber) {
                pageTable[i].valid = false;
                break;
            }
        }
    }else {
        frameNumber = findEmptyFrame();
    }

    loadPageToFrame(virtualPageNumber, frameNumber);
    replacementAlgorithm->accessPage(frameNumber);
}

bool VirtualMemoryManager::isPhysicalMemoryFull() {
    for (const Page& page : physicalMemory) {
        if (!page.valid) {
            return false;
        }
    }
    return true;
}

int VirtualMemoryManager::findEmptyFrame() {
    for (int i = 0; i < physicalMemory.size(); ++i) {
        if (!physicalMemory[i].valid) {
            return i;
        }
    }
    return -1;
}

void VirtualMemoryManager::loadPageToFrame(int virtualPageNumber, int frameNumber) {
    pageTable[virtualPageNumber].frameNumber = frameNumber;
    pageTable[virtualPageNumber].valid = true;
    physicalMemory[frameNumber].pageNumber = virtualPageNumber;
    physicalMemory[frameNumber].valid = true;
    physicalMemory[frameNumber].referenced = true;
    cout << "Load page: " << virtualPageNumber << " to frame: " << frameNumber << endl;
}

void VirtualMemoryManager::printPerformanceMetrics() {
    cout << "\nPerformance Metrics: " << endl;
    cout << setw(20) << left << "Total Page Accesses: " << totalPageAccesses << endl;
    cout << setw(20) << left << "Total Page Faults: " << pageFaults << endl;
}

void VirtualMemoryManager::printPhysicalMemory() {
    cout << "\nPages in Memory: " << endl;
    for (int i = 0; i < physicalMemory.size(); ++i) {
        if (physicalMemory[i].valid) {
            cout << setw(10) << left << "Frame " << setw(3) << i << ": Page " << setw(3) << physicalMemory[i].pageNumber << endl;
            int virtualStart = physicalMemory[i].pageNumber * pageSize;
            int virtualEnd = virtualStart + pageSize - 1;
            cout << setw(20) << left << "Virtual Address Range: " << virtualStart << " - " << virtualEnd << endl;
        } else {
            cout << "Frame: " << i << " is empty." << endl;
        }
    }
}

void VirtualMemoryManager::printPageTable() {
    cout << "Page Table:" << endl;
    cout << left << setw(15) << "Virtual Page" << setw(20) << "Physical Frame" << "Valid" << endl;
    cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    for (int i = 0; i < pageTable.size(); ++i) {
        cout << left << setw(15) << i << setw(20) << pageTable[i].frameNumber
             << (pageTable[i].valid ? "Yes" : "No") << endl;
    }
}


int VirtualMemoryManager::translateVirtualAddress(int virtualAddress) {
    int virtualPageNumber = virtualAddress / pageSize;
    int offset = virtualAddress % pageSize;

    PageTableEntry& pte = pageTable[virtualPageNumber];
    if (!pte.valid) {
        cout << "Page " << virtualPageNumber << " is not in the memory." << endl;
        return -1;
    }

    int physicalFrameNumber = pte.frameNumber;
    int physicalAddress = physicalFrameNumber * pageSize + offset;
    return physicalAddress;
}


int VirtualMemoryManager::translatePhysicalAddress(int physicalAddress) {
    int frameNumber = physicalAddress / pageSize;
    int offset = physicalAddress % pageSize;
    if (frameNumber <0 || frameNumber >= physicalMemory.size()) {
        cout << "Invalid physical frame number: " << frameNumber << endl;
        return -1;
    }

    Page& page = physicalMemory[frameNumber];
    if (!page.valid) {
        cout << "Physical frame " << frameNumber << " is not in the memory." << endl;
        return -1;
    }

    int virtualPageNumber = page.pageNumber;
    int virtualAddress = virtualPageNumber * pageSize + offset;
    return virtualAddress;
}