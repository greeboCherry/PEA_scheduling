#pragma once

#include <memory>
#include <iostream>

#include "fileReader.h"
#include "printTools.h"

class FileReaderTest
{
public:
    bool runTests()
    {
        bool result = true;

        shouldLoadFirstSet();
        shouldLoad4jobsSample();
        return true;
    }

    bool shouldLoadFirstSet()
    {
        auto sut = std::make_shared<FileReader>();
        //FileReader sut;
        std::vector<Task> output;
        sut->readWT("Input/wt40.txt", 1, output);

        std::cout << "output.size()" << output.size() << std::endl;

        return false;
    }

    bool shouldLoad4jobsSample()
    {
        auto sut = std::make_shared<FileReader>();

        std::vector<Task> output;
        sut->readWT("Input/wt4.txt", 1, output);

        std::cout << printTools::toString(output);

        std::cout << "output.size()" << output.size() << std::endl;

        return false;
    }

};