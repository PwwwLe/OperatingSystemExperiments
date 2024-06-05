//
// Created by Sliver on 24-5-29.
//

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <unordered_map>

#include "Directory.h"

// 文件权限常量
enum Permissions {
    READ = 1 << 0,     // 读权限
    WRITE = 1 << 1,    // 写权限
    EXECUTE = 1 << 2   // 执行权限
};

// 文件系统核心类，用于管理文件和目录
class FileSystem {
private:
    unique_ptr<Directory> root;                  // 根目录
    vector<bool> freeBlocks;                     // 块可用状态
    unordered_map<int, File*> fileDescriptorMap; // 文件描述符管理
    int nextFileDescriptor = 0;                  // 下一个可用的文件描述符

    // 获取目录
    // 参数:
    //   path - 目录的路径
    // 返回:
    //   指向目录的指针
    Directory *getDirectory(const string &path);

    // 分割路径
    // 参数:
    //   path - 目录路径
    // 返回:
    //   目录路径的各级目录名
    vector<string> splitPath(const string &path);

    // 解析权限
    // 参数:
    //   permissions - 权限字符串
    // 返回:
    //   权限的整数表示
    int parsePermissions(const string &permissions);

    // 查找文件
    // 参数:
    //   dir - 目录指针
    //   fileName - 文件名
    // 返回:
    //   指向文件的指针
    File *findFile(Directory *dir, const string &fileName);

    // 查找目录
    // 参数:
    //   dir - 目录指针
    //   dirName - 目录名
    // 返回:
    //   指向子目录的指针
    Directory *findDirectory(Directory *dir, const string &dirName);

public:
    // 构造函数
    FileSystem();

    // 创建文件
    // 参数:
    //   path - 目录路径
    //   fileName - 文件名
    //   permissions - 权限字符串
    void createFile(const string &path, const string &fileName, const string &permissions);

    // 打开文件
    // 参数:
    //   path - 目录路径
    //   fileName - 文件名
    // 返回:
    //   文件描述符
    int openFile(const string &path, const string &fileName);

    // 关闭文件
    // 参数:
    //   fileDescriptor - 文件描述符
    void closeFile(int fileDescriptor);

    // 读取文件
    // 参数:
    //   fileDescriptor - 文件描述符
    void readFile(int fileDescriptor);

    // 写入文件
    // 参数:
    //   fileDescriptor - 文件描述符
    //   data - 要写入的数据
    void writeFile(int fileDescriptor, const string &data);

    // 删除文件
    // 参数:
    //   path - 目录路径
    //   fileName - 文件名
    void deleteFile(const string &path, const string &fileName);

    // 创建目录
    // 参数:
    //   path - 目录路径
    //   dirName - 目录名
    void createDirectory(const string &path, const string &dirName);

    // 删除目录
    // 参数:
    //   path - 目录路径
    //   dirName - 目录名
    void deleteDirectory(const string &path, const string &dirName);

    // 列出目录内容
    // 参数:
    //   path - 目录路径
    void listDirectory(const string &path);
};


#endif //FILESYSTEM_H
