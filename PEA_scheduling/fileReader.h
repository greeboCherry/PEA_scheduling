#pragma once

#include <string>
#include <vector>
#include "Task.h"

class fileReader
{
public:
    fileReader();
    ~fileReader();
    /*
        format: row of times
                row of weights
                row of due dates
                other tasks
    */
    bool readWT(std::string path, int setNum, std::vector<Task>& output);
};

