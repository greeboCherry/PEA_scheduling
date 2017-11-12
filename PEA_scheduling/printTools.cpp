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
        result += "Task " + std::to_string(++i) + ": " + task.toString() + "\n";
    }
    return result;
}

std::string printTools::toString(std::vector<Task>& taskSet, std::vector<int>& taskOrder)
{
    std::string result;
    int i = 0;
    for each (auto const &id in taskOrder)
    {
        result += "Task " + std::to_string(++i) + ": " + taskSet[id].toString() + "\n";
    }
    return result;
}

std::string printTools::toString(std::vector<Task*> taskView)
{
    std::string result;
    int i = 0;
    for each (auto const &task in taskView)
    {
        result += "Task " + std::to_string(++i) + ": " + task->toString() + "\n";
    }
    return result;

}

