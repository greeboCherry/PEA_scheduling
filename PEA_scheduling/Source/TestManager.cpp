#include "TestManager.h"

#include "fileReaderTest.h"
#include "fileReader.h"
#include "BBScheduler.h"

TestManager::TestManager()
{

}


TestManager::~TestManager()
{
}

bool TestManager::runAllTests()
{
    bool result = true;

    FileReaderTest fileReaderTest;
    fileReaderTest.runTests();

    FileReader fr;
    std::vector<Task> tasks;
    fr.readWT("Input/wt40.txt", 1, tasks);

    BBScheduler BBsut(tasks);
    BBsut.schedule();


    int i = tasks.size();
    return result;
}
