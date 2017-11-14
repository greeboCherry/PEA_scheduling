// PEA_scheduling.cpp : Defines the entry point for the console application.
//

#include "TestManager.h"
#include "Timer.h"
#include "BBDFSScheduler.h"
#include "BBScheduler.h"
#include "printTools.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include "fileReader.h"

int main()
{
    //TestManager testManager;
    //testManager.runAllTests();

    FileReader fr;
    std::vector<Task> tasks;
    std::string filename = "Input/wt40.txt";
    fr.readWT(filename, 1, tasks);

    std::ofstream output("output/res.txt", std::ofstream::out | std::ofstream::app);
    if (!output.is_open())
        std::cout << "Couldn't open logger file ";
    Timer timer;
    timer.StartCounter();

    BBScheduler estimator(tasks);
    estimator.schedule();

    auto time = timer.GetCounter();

    output << "/////////// Opened " << filename << std::endl;
    std::cout << "Upper Bound estimated by sth like NAH: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    output << "Upper Bound estimated by sth like NAH: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    auto secondPart = estimator.getTasksDone();
    auto tardinessofFirstPart = estimator.calculateTardiness(estimator.getTasksLeft(), 0);

    std::cout << printTools::toString(secondPart) << std::endl;
    output << printTools::toString(secondPart) << std::endl;



    // pass non scheduled tasks to DFS scheduler
    BBDFSScheduler sut(estimator.getTasksLeft());
    sut.upperBound = tardinessofFirstPart + 1;

    sut.upperBound = 9999;

    timer.StartCounter();

    sut.schedule();
    
    time = timer.GetCounter();

    std::cout << "Weighted tardiness: " << sut.upperBound << std::endl;
    std::cout << "Result by BnB - Weighted tardiness: " << estimator.upperBound << " after " << time << " ms " << std::endl;

    output << "Weighted tardiness: " << sut.upperBound << std::endl;
    output << "Result by BnB - Weighted tardiness: " << estimator.upperBound << " after " << time << " ms " << std::endl;

    auto finalResult = sut.getTasksDone();
    auto firstPart = estimator.getTasksDone();
    std::copy(secondPart.begin(), secondPart.end(), std::back_inserter(finalResult));
    auto finalTardiness = sut.calculateTardiness(finalResult);
    auto msg = printTools::toString(finalResult);
    output << msg;
    std::cout << msg;

    std::cout << "Press enter or sth: ";
    std::cin.get();
    return 0;
}

