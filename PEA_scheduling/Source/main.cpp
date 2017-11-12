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

#include "fileReader.h"

int main()
{
    //TestManager testManager;
    //testManager.runAllTests();

    FileReader fr;
    std::vector<Task> tasks;
    fr.readWT("Input/wt15.txt", 1, tasks);

    std::ofstream output("output/res.txt", std::ofstream::out | std::ofstream::app);
    Timer timer;
    timer.StartCounter();

    BBScheduler estimator(tasks);
    estimator.schedule();

    auto time = timer.GetCounter();
    std::cout << "Upper Bound estimated by sth like NAH: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    output << "Upper Bound estimated by sth like NAH: " << estimator.upperBound << " after " << time << " ms " << std::endl;

    BBDFSScheduler sut(tasks);
    sut.upperBound = estimator.upperBound + 1;

    timer.StartCounter();

    sut.schedule();
    
    time = timer.GetCounter();

    std::cout << "Weighted tardiness: " << sut.upperBound << std::endl;

    std::cout << "Result by BnB - Weighted tardiness: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    std::cout << printTools::toString(tasks, sut.bestSoFar);


    output << "Weighted tardiness: " << sut.upperBound << std::endl;

    output << "Result by BnB - Weighted tardiness: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    output << printTools::toString(tasks, sut.bestSoFar);

    std::cout << "Press enter or sth: ";
    std::cin.get();
    return 0;
}

