#include <printTools.h>

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"

std::string printTools::toString(std::vector<Task>& taskView)
{
    std::string result;
    int i = 0;
    for each (auto const &task in taskView)
    {
        result += "Task " + std::to_string(++i) + ": " + task.toString() + "\t";
    }
    return result;

}
