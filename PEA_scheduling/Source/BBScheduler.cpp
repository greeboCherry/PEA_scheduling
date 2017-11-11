#include "BBScheduler.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <iterator>
#include "printTools.h"

namespace
{



}

BBScheduler::Solution::Solution(Solution& parentInstance, unsigned taskNumber)
{
    tasksDone.reserve(parentInstance.tasksDone.size() + 1);
    tasksAvailable.reserve(parentInstance.tasksAvailable.size() - 1);
    tasksDone.push_back(parentInstance.tasksAvailable[taskNumber]);
    std::copy(parentInstance.tasksDone.begin(), parentInstance.tasksDone.end(), std::back_inserter(tasksDone));
    std::copy(parentInstance.tasksAvailable.begin(), parentInstance.tasksAvailable.begin() + taskNumber, std::back_inserter(tasksAvailable));
    std::copy(parentInstance.tasksAvailable.begin() + taskNumber + 1, parentInstance.tasksAvailable.end(), std::back_inserter(tasksAvailable));
}

BBScheduler::Solution::Solution(int instanceSize)
{
    tasksDone.reserve(instanceSize);
}

BBScheduler::BBScheduler(std::vector<Task>& pTasks) : Scheduler(pTasks)
{

}

void BBScheduler::schedule()
{
    std::cout << "Unsorted Tasks* \n" << printTools::toString(tasksLeft);

    int taskCount = tasksLeft.size();

    //sort tasks by deadline ascending
    std::sort(tasksLeft.begin(), tasksLeft.end(), [](Task* left, Task* right)
    {
        return left->deadline < right->deadline;
    });

    std::cout << "Sorted Tasks* \n" << printTools::toString(tasksLeft);

    auto upperBound = calculateTardiness(tasksLeft, 0);

    std::cout << "Initial Tardiness: " << calculateTardiness(tasksLeft,0) << " or " << calculateCompletitionTimeAndTardiness(tasksLeft, 0).second << std::endl;
    //initialize initial n Solutions
    Solution gold(taskCount);
    std::copy(tasksLeft.begin(), tasksLeft.end(), std::back_inserter(gold.tasksAvailable));
    std::cout << "Gold Tardiness: " << calculateTardiness(gold.tasksAvailable, 0) << std::endl;
    for (unsigned i = 0; i < tasksLeft.size(); i++)
    {
        solutions.emplace_back(gold, i);

        //DEBUG BELOW
        auto temp = calculateCompletitionTimeAndTardiness(solutions.back().tasksAvailable, 0);
        auto midTime = temp.first;
        auto thisTar = temp.second;
        thisTar += calculateTardiness(solutions.back().tasksDone, midTime);
        std::cout << "Initial " << i << "th WT " << thisTar << std::endl;
    }
    for (int i = 1; i < taskCount; i++)
    {
        branchOutAll();
        cutBranches(upperBound);
    }
    std::cout << "Branches atm: " << solutions.size() << " WT = " << calculateTardiness(solutions[0].tasksDone, 0) << std::endl;
    std::cout << printTools::toString(solutions[0].tasksDone) << std::endl;
}

void BBScheduler::cutBranches(int &upperBound)
{
    std::vector<Solution> viableSolutions;
    viableSolutions.reserve(solutions.size());
    
    //make list of solutions with the lowest tardiness;
    for each (auto& sol in solutions)
    {
        auto temp = calculateCompletitionTimeAndTardiness(sol.tasksAvailable, 0);
        auto midTime = temp.first;
        auto thisTar = temp.second;
        thisTar += calculateTardiness(sol.tasksDone, midTime);
        if (thisTar <= upperBound)
        {
            if (thisTar < upperBound)
            {
                viableSolutions.clear();
                upperBound = thisTar;
            }
                viableSolutions.push_back(sol);
        }
    }
    solutions = viableSolutions;
}

void BBScheduler::branchOutAll()
{
    
    auto oldSize = solutions.size();
    solutions.reserve(oldSize*(solutions[0].tasksAvailable.size()+1));
    auto i = 0u;
    for (auto it = solutions.begin(); i < oldSize; it++, i++)
    {
        branch(*it);
    }
    auto out = solutions.max_size();
    solutions.erase(solutions.begin(), solutions.begin() + oldSize);
    
}

void BBScheduler::branch(Solution& instance)
{
    for (auto i = 0u; i < instance.tasksAvailable.size(); i++)
    {
        solutions.emplace_back(Solution(instance, i));
    }

    //solutions.push_back()
}


