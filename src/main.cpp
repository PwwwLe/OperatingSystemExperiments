#include "exp1/PCB.h"
#include "exp1/FCFS.h"
#include "exp1/SJF.h"
#include "exp1/RR.h"
#include "exp1/MLFQ.h"
#include "exp1/PerformanceMetrics.h"


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <thread>

#include "exp2/VirtualMemoryManager.h"

#include "exp3/FileSystem.h"


using namespace std;

void printDivider(char fillChar = '-', int width = 150) {
    cout << setfill(fillChar) << setw(width) << fillChar << setfill(' ') << endl;
}

// 实验一代码
/*
void printProcessHeader() {
    cout << left
            << setw(15) << "Process ID"
            << setw(15) << "Arrival Time"
            << setw(15) << "Burst Time"
            << setw(15) << "Start Time"
            << setw(15) << "Finish Time"
            << setw(15) << "Waiting Time"
            << endl;
    cout << setfill('-') << setw(90) << "-" << endl;
    cout << setfill(' ');
}

void printProcessInfo(const PCB &process) {
    cout << left
            << setw(15) << process.getProcessID()
            << setw(15) << process.getArrivalTime()
            << setw(15) << process.getBurstTime()
            << setw(15) << process.getStartTime()
            << setw(15) << process.getFinishTime()
            << setw(15) << process.getWaitingTime()
            << endl;
}

void display(const vector<PCB> &processes) {
    printProcessHeader();
    for (const PCB &process: processes) {
        printProcessInfo(process);
    }

    cout << "\nPerformance Metrics:" << endl;
    cout << "Average Turnaround Time: " << calculateAverageTurnaroundTime(processes) << endl;
    cout << "Average Weighted Turnaround Time: " << calculateAverageWeightedTurnaroundTime(processes) << endl;
    cout << "Average Waiting Time: " << calculateAverageWaitingTime(processes) << endl;
    cout << endl;
    cout << endl;
}


vector<PCB> generateTestData(int numProcesses) {
    vector<PCB> processes;
    srand(time(nullptr)); // 设置随机种子

    for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime = rand() % 20; // 到达时间在0到19之间随机
        int burstTime = rand() % 10 + 1; // 运行时间在1到10之间随机
        int priority = rand() % 5 + 1; // 优先级在1到5之间随机

        PCB process(i + 1, READY, priority, arrivalTime, burstTime);
        processes.push_back(process);
    }

    return processes;
}
*/

// 实验三控制台用户界面
void userInterface(FileSystem &fs) {
    string command;
    while (true) {
        cout << endl << "请输入命令（输入 'help' 查看帮助， 'exit' 退出）： " << endl;
        getline(cin, command);

        if (command == "exit") {
            break;
        }

        istringstream iss(command);
        string cmd, arg1, arg2, arg3, arg4;
        iss >> cmd >> arg1 >> arg2 >> arg3 >> arg4;

        try {
            if (cmd == "create") {
                if (arg1 == "file") {
                    if (arg4.empty()) {
                        cout << "错误：缺少文件权限参数" << endl;
                        continue;
                    }
                    fs.createFile(arg2, arg3, arg4);
                } else if (arg1 == "dir") {
                    fs.createDirectory(arg2, arg3);
                } else {
                    cout << "无效的命令参数" << endl;
                }
            } else if (cmd == "open") {
                if (arg1 == "file") {
                    int fd = fs.openFile(arg2, arg3);
                    cout << "文件描述符：" << fd << endl;
                } else {
                    cout << "无效的命令参数" << endl;
                }
            } else if (cmd == "close") {
                int fd = stoi(arg1);
                fs.closeFile(fd);
            } else if (cmd == "read") {
                int fd = stoi(arg1);
                fs.readFile(fd);
            } else if (cmd == "write") {
                int fd = stoi(arg1);
                fs.writeFile(fd, arg2);
            } else if (cmd == "delete") {
                if (arg1 == "file") {
                    fs.deleteFile(arg2, arg3);
                } else if (arg1 == "dir") {
                    fs.deleteDirectory(arg2, arg3);
                } else {
                    cout << "无效的命令参数" << endl;
                }
            } else if (cmd == "list") {
                fs.listDirectory(arg1);
            } else if (cmd == "help") {
                printDivider();
                cout << left << setw(15) << "cmd" << setw(40) << "arg1" << setw(30) << "arg2" << setw(30) << "arg3" <<
                        setw(30) << "arg4" << endl;
                printDivider();
                cout << left << setw(15) << "create" << setw(40) << "file" << setw(30) << "<路径：path>" << setw(30) <<
                        "<文件名：fileName>" << setw(30) << "<访问权限：permissions>" << endl;
                cout << left << setw(15) << "create" << setw(40) << "dir" << setw(30) << "<路径：path>" << setw(30) <<
                        "<目录名：dirName>" << endl;
                cout << left << setw(15) << "open" << setw(40) << "file" << setw(30) << "<路径：path>" << setw(30) <<
                        "<文件名：fileName>" << endl;
                cout << left << setw(15) << "close" << setw(40) << "<文件描述符：fileDescriptor>" << endl;
                cout << left << setw(15) << "read" << setw(40) << "<文件描述符：fileDescriptor>" << endl;
                cout << left << setw(15) << "write" << setw(40) << "<文件描述符：fileDescriptor>" << setw(30) << setw(30) << "<数据：data>"
                        << endl;
                cout << left << setw(15) << "delete" << setw(40) << "file" << setw(30) << "<路径：path>" << setw(30) <<
                        "<文件名：fileName>" << endl;
                cout << left << setw(15) << "delete" << setw(40) << "dir" << setw(30) << "<路径：path>" << setw(30) <<
                        "<目录名：dirName>" << endl;
                cout << left << setw(15) << "list" << setw(40) << "<路径：path>" << endl;
                cout << left << setw(15) << "help" << endl;
                cout << left << setw(15) << "exit" << endl;
                printDivider();
            } else {
                cout << "无效命令" << endl;
            }
        } catch (const exception &e) {
            cout << "错误：" << e.what() << endl;
        }
    }
}

int main() {
    // Experiment 1:

    // int numProcesses = 10;
    /*
    vector<PCB> testData = generateTestData(numProcesses);
    */
    /*
    vector<PCB> testData;
    PCB p1(1, READY, 0, 0, 3);
    testData.push_back(p1);
    PCB p2(2, READY, 0, 4, 2);
    testData.push_back(p2);
    PCB p3(3, READY, 0, 4, 1);
    testData.push_back(p3);
    PCB p4(4, READY, 0, 7, 4);
    testData.push_back(p4);
    PCB p5(5, READY, 0, 8, 5);
    testData.push_back(p5);
    PCB p6(6, READY, 0, 8, 8);
    testData.push_back(p6);
    PCB p7(7, READY, 0, 11, 3);
    testData.push_back(p7);
    PCB p8(8, READY, 0, 15, 4);
    testData.push_back(p8);
    PCB p9(9, READY, 0, 15, 7);
    testData.push_back(p9);
    PCB p10(10, READY, 0, 17, 10);
    testData.push_back(p10);

    cout << "Initial Processes: " << endl;

    printProcessHeader();
    for (const PCB &process: testData) {
        printProcessInfo(process);
    }
    cout << endl;
    cout << endl;

    cout << "FCFS Algorithms: " << endl;
    FCFS fcfsScheduler(testData);
    vector<PCB> fcfsFinishedProcesses = fcfsScheduler.schedule();
    display(fcfsFinishedProcesses);

    cout << "SJF Algorithms: " << endl;
    SJF sjfScheduler(testData);
    vector<PCB> sjfFinishedProcesse = sjfScheduler.schedule();
    display(sjfFinishedProcesse);

    cout << "RR Algorithms: " << endl;
    RR rrScheduler(testData, 5);
    vector<PCB> rrFinishedProcesses = rrScheduler.schedule();
    display(rrFinishedProcesses);

    cout << "MLFQ Algorithms: " << endl;
    vector<int> quantums = {1, 2, 4};
    MLFQ mlfqScheduler(3, testData, quantums);
    vector<PCB> mlfqFinishedProcesses = mlfqScheduler.schedule();
    display(mlfqFinishedProcesses);
    */

    /*
    // Experiment 2
    // 配置内存常量
    const int numPages = 4;     // 物理内存中的帧数量
    const int numVirtualPages = 8;      // 虚拟内存中的页面数量
    const int pageSize = 1024;      // 页面大小
    const int maxAddress = numVirtualPages * pageSize;      // 可寻址的最大虚拟内存大小

    // 初始化虚拟内存管理器，默认使用 FIFO 页面替换策略
    VirtualMemoryManager vmm(FIFO, numPages, numVirtualPages, pageSize);
    string command;

    // 交互式界面循环
    while (true) {
        // 显示操作菜单
        printDivider();
        cout << endl << "Please enter a command:" << endl;
        cout << setw(2) << right << "1. " << "Access virtual address" << endl;
        cout << setw(2) << right << "2. " << "Query virtual address to physical address translation" << endl;
        cout << setw(2) << right << "3. " << "Query physical address to virtual address translation" << endl;
        cout << setw(2) << right << "4. " << "Change page replacement policy" << endl;
        cout << setw(2) << right << "5. " << "Display page information in physical memory" << endl;
        cout << setw(2) << right << "6. " << "Display page table" << endl;
        cout << setw(2) << right << "7. " << "Display performance metrics" << endl;
        cout << setw(2) << right << "8. " << "Exit" << endl;
        printDivider();

        // 读取用户指令
        cout << "Enter your instruction: ";
        cin >> command;
        int commandInt;
        try {
            commandInt = stoi(command);     // 将字符串转换为整数
        } catch (invalid_argument&) {
            cout << "Invalid command. Please enter again." << endl;
            continue;
        }

        // 处理命令
        switch (commandInt) {
            case 1: {
                // 访问虚拟地址
                int virtualAddress;
                printDivider();
                cout << "Please enter the virtual address: ";
                cin >> virtualAddress;
                if (virtualAddress < 0 || virtualAddress > maxAddress) {
                    cout << "Invalid virtual address. Please enter a valid virtual address." << endl;
                } else {
                    int virtualPageNumber = virtualAddress / pageSize;
                    int offset = virtualAddress % pageSize;
                    vmm.accessPage(virtualPageNumber);
                    cout << "Virtual address " << virtualAddress << " is accessed." << endl;
                }
                break;
            }
            case 2: {
                // 查询虚拟地址到物理地址的转换
                int virtualAddress;
                printDivider();
                cout << "Please enter the virtual address: ";
                cin >> virtualAddress;
                int physicalAddress = vmm.translateVirtualAddress(virtualAddress);
                if (physicalAddress != -1) {
                    cout << "Virtual address: " << virtualAddress << " translate to physical address: " <<
                            physicalAddress
                            << endl;
                } else {
                    cout << "Unable to translate, invalid virtual address." << endl;
                }
                break;
            }
            case 3: {
                // 查询物理地址到虚拟地址的转换
                int physicalAddress;
                printDivider();
                cout << "Please enter the physical address: ";
                cin >> physicalAddress;
                int virtualAddress = vmm.translatePhysicalAddress(physicalAddress);
                if (virtualAddress != -1) {
                    cout << "Physical address: " << physicalAddress << " translate to virtual address: " <<
                            virtualAddress
                            << endl;
                } else {
                    cout << "Unable to translate, invalid physical address." << endl;
                }
                break;
            }
            case 4: {
                // 更改页面替换策略
                printDivider();
                cout << endl << "Please select a page replacement policy: " << endl;
                cout << "1. FIFO" << endl;
                cout << "2. LRU" << endl;
                cout << "3. CLOCK" << endl;
                cout << "4. RANDOM" << endl;
                printDivider();

                int choice;
                cout << "Enter your instruction: ";
                cin >> choice;
                ReplacementPolicy selectedPolicy;
                switch (choice) {
                    case 1:
                        selectedPolicy = FIFO;
                        break;
                    case 2:
                        selectedPolicy = LRU;
                        break;
                    case 3:
                        selectedPolicy = CLOCK;
                        break;
                    case 4:
                        selectedPolicy = RANDOM;
                        break;
                    default:
                        cout << "Invalid choice. Please select a valid page replacement policy." << endl;
                        continue;
                }
                vmm.setReplacementPolicy(selectedPolicy);
                cout << "Page replacement policy has changed. "<< endl;
                break;
            }
            case 5: {
                // 显示物理内存中的页面信息
                printDivider();
                vmm.printPhysicalMemory();
                printDivider();
                break;
            }
            case 6: {
                // 显示页表信息
                printDivider();
                vmm.printPageTable();
                printDivider();
                break;
            }
            case 7: {
                // 显示性能指标
                printDivider();
                vmm.printPerformanceMetrics();
                printDivider();
                break;
            }
            case 8: {
                // 退出程序
                printDivider();
                cout << "Exiting program..." << endl;
                return 0;
            }
            default: {
                    cout << "Invalid command. Please enter a valid command." << endl;
            }
        }
    }
    */


    // Experiment 3
    FileSystem fs;
    userInterface(fs);

    return 0;
}
