//
// Created by Sliver on 24-5-29.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"

class Directory {
public:
    string name;
    vector<unique_ptr<File>> files;
    vector<unique_ptr<Directory>> directories;

    Directory(const string& name);
};



#endif //DIRECTORY_H
