#include "Scheduler.h"

#include <utility>

Scheduler::Scheduler(std::vector<Task>& pTasks)
{
    tasksLeft.reserve(pTasks.size());
    taskSet = pTasks;
    for (auto it = pTasks.begin(); it != pTasks.end(); it++)    //todo std::transform here?
    {
        tasksLeft.push_back(&(*it)); //that's how you make pointer from iterator, ffs1
    }
}

Scheduler::~Scheduler()
{
}

std::pair<int,int> Scheduler::calculateCompletitionTimeAndTardiness(const std::vector<Task*>& tasks, int time)
{
    int tardiness = 0;

    for (auto it = tasks.begin(); it != tasks.end(); it++)
    {
        time += it[0]->timeRequired; //yes, that's how you iterate over vector of pointers...
        int overdue = time - it[0]->deadline;
        if (overdue > 0)
        {
            tardiness += overdue * it[0]->weight;
        }
        ;
    }
    return std::make_pair(time, tardiness);

}

int Scheduler::calculateTardiness(const std::vector<Task*>& tasks, int time /*= 0*/)
{
    int result = 0;
    for (auto it = tasks.begin(); it != tasks.end(); it++)
    {
        time += it[0]->timeRequired; //yes, that's how you iterate over vector of pointers...
        int overdue = time - it[0]->deadline;
        if (overdue > 0)
        {
            result += overdue * it[0]->weight;
        }
    }
    return result;
}

int Scheduler::calculateTardiness(const std::vector<Task>& tasks, int time /*= 0*/)
{
    int result = 0;
    for (auto it = tasks.begin(); it != tasks.end(); it++)
    {
        time += it->timeRequired;
        int overdue = time - it->deadline;
        if (overdue > 0)
        {
            result += overdue * it->weight;
        }
    }
    return result;
}

std::vector<Task> Scheduler::getTasksLeft()
{
    std::vector<Task> ret;
    ret.reserve(tasksLeft.size());

    for each (auto task in tasksLeft)
    {
        ret.push_back(*task);
    }
    return ret;
}

std::vector<Task> Scheduler::getTasksDone()
{
    std::vector<Task> ret;
    ret.reserve(tasksDone.size());

    for each (auto task in tasksDone)
    {
        ret.push_back(*task);
    }
    return ret;
}
