#include "BBDFSScheduler.h"
#include "printTools.h"


#include <iterator>
#include <numeric>

BBDFSScheduler::BBDFSScheduler(std::vector<Task>& pTasks) : Scheduler(pTasks)
{
}
BBDFSScheduler::~BBDFSScheduler()
{
}
void BBDFSScheduler::schedule()
{
    std::vector<int> tasksDone;
    std::vector<int> tasksLeft(taskSet.size());
    std::iota(tasksLeft.begin(), tasksLeft.end(), 0);
    recursive(tasksDone, tasksLeft, 0, 0, 0);
    tasksDone.reserve(taskSet.size());
    for each (auto var in bestSoFar)
    {
        this->tasksDone.push_back(&(taskSet[var]));

    }
}

int BBDFSScheduler::calculateDelta(unsigned newTask, std::vector<int>& tasksDone, std::vector<int>& tasksLeft, unsigned timePassed)
{
    const auto& temp = taskSet[tasksLeft[newTask]]; // that's all because of using indexes instead of pointers, but it's fine, time is short

    timePassed += temp.timeRequired; //it's copy on stack, it's fine
    int overdue = timePassed - temp.deadline;
    if (overdue > 0)
        return overdue*temp.weight;
    else return 0;
}

void BBDFSScheduler::recursive(std::vector<int>& tasksDone, std::vector<int>& tasksLeft, unsigned backtrace, int weightedTardiness, unsigned timePassed)
{
            // if it's leaf
    if (tasksDone.size() == taskSet.size())
    {
        if (weightedTardiness < upperBound)
        {
            bestSoFar = tasksDone;
            upperBound = weightedTardiness;
        }
    }
    else    // if it's not
    {
        for (auto i = 0u; i < tasksLeft.size(); i++)
        {
            int deltaTardiness = calculateDelta(i, tasksDone, tasksLeft, timePassed);
            int deltaTime = taskSet[tasksLeft[i]].timeRequired;

            weightedTardiness += deltaTardiness;
            timePassed += deltaTime;

            if (weightedTardiness < upperBound)
            {
                tasksDone.push_back(tasksLeft[i]);
                tasksLeft.erase(tasksLeft.begin() + i);
    //DEBUG LOG
              /* std::copy(tasksDone.begin(), tasksDone.end(),
                    std::ostream_iterator<int>(std::cout, ", "));
                std::cout << ": " << weightedTardiness << std::endl;*/

                recursive(tasksDone, tasksLeft, i, weightedTardiness, timePassed);
            }
        
        weightedTardiness -= deltaTardiness;
        timePassed -= deltaTime;
        }
    }
    if(tasksDone.size())
    {
        tasksLeft.insert(tasksLeft.begin() + backtrace, tasksDone.back());
        tasksDone.pop_back();
    }
    
}
