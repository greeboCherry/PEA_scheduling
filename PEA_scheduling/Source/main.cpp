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
    
    std::ofstream output("output/res.txt", std::ofstream::out | std::ofstream::app);
    if (!output.is_open())
        std::cout << "Couldn't open logger file output/res.txt";
    std::cout << "Enter filename in format <wtSIZE.txt> ie. Input/wt40constructAdditionalPylons.txt" << std::endl;
    std::string filename = "Input/wt50.txt";
    std::cin >> filename;

    
    if (!fr.readWT(filename, 1, tasks))
    {
        std::cout << "Can't open " << filename;
        return 1;
    }

    output << "/////////// Opened " << filename << std::endl;
    
    Timer timer;

    timer.StartCounter();
    BBScheduler estimator(tasks); //that's just to calculate uppper bound, estimator estimates!
    //estimator.fruitlessLevelsLeft = 20;
    estimator.schedule();

    auto time = timer.GetCounter();

    
    std::cout << "Upper Bound estimated by sth like NAH: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    output << "Upper Bound estimated by sth like NAH: " << estimator.upperBound << " after " << time << " ms " << std::endl;
    
        // pass non scheduled tasks to DFS scheduler
    BBDFSScheduler sut(tasks);
    sut.upperBound = estimator.upperBound + 1;
    sut.maxTime = estimator.maxTime;

    timer.StartCounter();

    sut.schedule();
    
    time = timer.GetCounter();

    std::cout << "Result by BnB - Weighted tardiness: " << sut.upperBound << " after " << time << " ms " << std::endl;
    output << "Result by BnB - Weighted tardiness: " << sut.upperBound << " after " << time << " ms " << std::endl;

    auto finalResult = sut.getTasksDone();
    auto msg = printTools::toString(finalResult);
    output << msg;
    std::cout << msg;

    std::cout << "Press enter or sth: ";
    std::cin.get();
    output.close();
    return 0;
}

