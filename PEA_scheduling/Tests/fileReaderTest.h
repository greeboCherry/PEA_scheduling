#pragma once

#include <memory>
#include <iostream>

#include "fileReader.h"


class FileReaderTest
{
public:
    bool runTests()
    {
        bool result = true;

        shouldLoadFirstSet();
        return true;
    }

    bool shouldLoadFirstSet()
    {
        auto sut = std::make_shared<FileReader>();
        //FileReader sut;
        std::vector<Task> output;
        sut->readWT("Input/wt40.txt", 1, output);

        std::cout << "output.size()" << output.size();


        return false;
    }

};