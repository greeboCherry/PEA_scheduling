#pragma once
#include "Scheduler.h"
#include "fileReader.h"

class BBDFSScheduler : public Scheduler
{
public:
    ~BBDFSScheduler();

    BBDFSScheduler(std::vector<Task>& pTasks);
    virtual void schedule() override;

    int upperBound = 99999;
    int maxTime = 99999;
    std::vector<int> bestSoFar;
    
protected:
    int calculateDelta(unsigned newTask, std::vector<int>& tasksDone, std::vector<int>& tasksLeft, unsigned timePassed);
    void recursive(std::vector<int>& tasksDone, std::vector<int>& taksLeft, unsigned backtrace, int weightedTardiness, int timePassed);

};

