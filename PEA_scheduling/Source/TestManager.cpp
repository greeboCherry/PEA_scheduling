#include "TestManager.h"

#include "fileReaderTest.h"

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

    return result;
}
