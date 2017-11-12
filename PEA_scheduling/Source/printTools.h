#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Task.h"


namespace printTools
{
    std::string toString(std::vector<Task>& taskView);
    std::string toString(std::vector<Task*> taskView);
    std::string toString(std::vector<Task>& taskSet, std::vector<int>& taskOrder);

}

