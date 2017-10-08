#pragma once

#include <vector>
#include <memory>

#include "Task.h"
//class Task;

/*
This virtual class is supposed to take reference to vector of tasks, and use only pointers to them so we don't waste time on copying and stuff
*/
class Scheduler
{
public:
    Scheduler(std::vector<Task>& pTasks)
    {
        tasksLeft.reserve(pTasks.size());
        for (auto it = pTasks.begin(); it != pTasks.end(); it++)
        {
            Task* ptr = &*it;   //that's how you make pointer from iterator, ffs
            tasksLeft.push_back(ptr);
        }
    };
    virtual ~Scheduler();

    //virtual void Schedule();

private:
    int currentTime;
    std::vector<Task*> tasksLeft;   //TODO KOZIEL maybe it can be one vector with border between them? that's what erase is for, right? 
    std::vector<Task*> tasksDone;
};

