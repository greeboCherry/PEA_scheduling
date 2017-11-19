#pragma once
#include "Scheduler.h"
class BBScheduler : public Scheduler
{
    struct Solution
    {
        Solution(int instanceSize);
        //take all tasks done by parent and "do" one of tasks availably 
        Solution(Solution& parentInstance, unsigned taskNumber);

        std::vector<Task*> tasksDone;
        std::vector<Task*> tasksAvailable;
    };

public:
    BBScheduler(std::vector<Task>& pTasks);
    virtual void schedule() override;
    int upperBound = 999999;
    int maxTime;
    int fruitlessLevelsLeft = 2;
protected:
    std::vector<Solution> solutions;
    unsigned branchLevel = 0;
    void branchOutAll();
    void branch(Solution& instance);
    bool cutBranches(int &upperBound);
};

