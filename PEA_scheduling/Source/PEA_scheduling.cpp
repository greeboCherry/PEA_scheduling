// PEA_scheduling.cpp : Defines the entry point for the console application.
//

#include "TestManager.h"

#include <memory>
#include <iostream>

#include "fileReader.h"

int main()
{
    TestManager testManager;
    testManager.runAllTests();

    std::cin.get();
    return 0;
}

