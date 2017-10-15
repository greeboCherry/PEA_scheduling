#include "Task.h"

#include <string>

Task::Task()
{
}


std::string Task::toString() const
{
    std::string result("Time: " + std::to_string(timeRequired)
        + ", Weight: " + std::to_string(weight) + ", Deadline: " + std::to_string(deadline));

    return result; 

}

Task::~Task()
{
}
