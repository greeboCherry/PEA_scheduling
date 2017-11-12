#pragma once
#include "Scheduler.h"
#include "fileReader.h"

class BBDFSScheduler : public Scheduler
{
public:
    ~BBDFSScheduler();

    BBDFSScheduler(std::vector<Task>& pTasks);
    virtual void schedule() override;

    int lowerbound = 0;
    int upperBound = 9999;
    std::vector<int> bestSoFar;
protected:
    int calculateDelta(unsigned newTask, std::vector<int>& tasksDone, std::vector<int>& tasksLeft, unsigned timePassed);
    void recursive(std::vector<int>& tasksDone, std::vector<int>& taksLeft, unsigned backtrace, int weightedTardiness, unsigned timePassed);

};

