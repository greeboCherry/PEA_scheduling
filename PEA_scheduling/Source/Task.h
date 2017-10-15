#pragma once

#include <string>
#include <vector>

struct Task
{
public:
    Task();
    Task(int pTime, int pWeight, int pDeadline) :
        timeRequired(pTime), 
        weight(pWeight), 
        deadline(pDeadline)
    {};

    std::string toString() const;

    ~Task();
    
    int timeRequired;
    int weight;
    int deadline;

};

