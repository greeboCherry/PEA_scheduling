#pragma once

#include <string>
#include <vector>
#include "Task.h"

class FileReader
{
public:
    FileReader();
    ~FileReader();
    /*
        format: row of times
                row of weights
                row of due dates
                other tasks
    */
    bool readWT(std::string path, int setNum, std::vector<Task>& output);
};

