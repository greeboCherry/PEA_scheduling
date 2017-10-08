#pragma once
class Task
{
public:
    Task();
    Task(int pTime, int pWeight, int pDeadline) :
        timeRequired(pTime), 
        weight(pWeight), 
        deadline(pDeadline)
    {};

    ~Task();
    
    int timeRequired;
    int weight;
    int deadline;

};

