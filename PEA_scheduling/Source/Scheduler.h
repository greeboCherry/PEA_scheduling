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
    Scheduler(std::vector<Task>& pTasks);
    virtual ~Scheduler();


    std::pair<int,int> calculateCompletitionTimeAndTardiness(const std::vector<Task*>& tasks, int time);
    //calculate Tardiness with given order of tasks and initial time(useful when trying to start from the end of time line
    int calculateTardiness(const std::vector<Task*>& tasks, int startTime = 0);
    int calculateTardiness(const std::vector<Task>& tasks, int startTime = 0);
    virtual void schedule()=0;

    std::vector<Task> getTasksLeft();
    std::vector<Task> getTasksDone();

protected:
    int currentTime;
    std::vector<Task> taskSet;
    std::vector<Task*> tasksLeft;   //TODO KOZIEL maybe it can be one vector with border between them? that's what erase is for, right? 
    std::vector<Task*> tasksDone;
};

