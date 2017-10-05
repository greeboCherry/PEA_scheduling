#include "fileReader.h"

#include <fstream>
#include <iostream>

fileReader::fileReader()
{
}


fileReader::~fileReader()
{
}

namespace
{
    int getInstanceSize(std::fstream &file)
    {
        std::string line;
        int currentRow = 0;
        file >> line;
        file.clear();
        file.seekg(0);
        return std::count(line.begin(), line.end(), ' ') + 1;
    }


    void LoadParametersFromInstanec(const int setSize, std::fstream& file, std::vector<Task> &output)
    {
        for (int i = 0; i < setSize; i++)
        {
            file >> output[i].timeRequired;
        }

        for (int i = 0; i < setSize; i++)
        {
            file >> output[i].weight;
        }

        for (int i = 0; i < setSize; i++)
        {
            file >> output[i].deadline;
        }
    }

}

bool fileReader::readWT(std::string path, int setNum, std::vector<Task>& output)
{
    std::fstream file(path, std::fstream::in);

    if (!file || !file.good())
    {
        std::cerr << "Couldn't open file at: " << path.c_str() << std::endl;
        return false;
    }

    const int setSize = getInstanceSize(file);
    int currentSet = 1;

    output.resize(setSize);

    LoadParametersFromInstanec(setSize, file, output);
    currentSet++;

    return true;
}
