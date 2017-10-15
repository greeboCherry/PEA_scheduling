#include "fileReader.h"

#include <fstream>
#include <iostream>
#include <regex>

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

namespace
{
    //this method counts words in line, not really what is needed here
    int getInstanceSize(std::fstream &file)
    {
        std::string line;
        std::getline(file, line);
        std::cout << line;
        file.clear();
        file.seekg(0);
        const std::regex expression("[^\\s]+", std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        return std::distance(
            std::sregex_iterator(line.begin(), line.end(), expression),
            std::sregex_iterator());

        return std::count(line.begin(), line.end(), ' ') + 1;
    }

    //call when next << operator is going to read first paramater of set
    void LoadParametersFromInstance(const int taskCount, std::fstream& file, std::vector<Task> &output)
    {
        for (int i = 0; i < taskCount; i++)
        {
            file >> output[i].timeRequired;
        }

        for (int i = 0; i < taskCount; i++)
        {
            file >> output[i].weight;
        }

        for (int i = 0; i < taskCount; i++)
        {
            file >> output[i].deadline;
        }
    }

}

bool FileReader::readWT(std::string path, int setNum, std::vector<Task>& output)
{
    std::fstream file(path, std::fstream::in);

    if (!file || !file.good())
    {
        std::cerr << "Couldn't open file at: " << path.c_str() << std::endl;
        return false;
    }
    //wt40.txt - find setSize in filename
    auto dotPos = path.find(".");
    auto wtPos = path.find("wt") + 2;
    auto setSizeStr = path.substr(wtPos, dotPos - wtPos);
    const int setSize = atoi(setSizeStr.c_str());
    
    int currentSet = 1;

    output.resize(setSize);

    LoadParametersFromInstance(setSize, file, output);
    currentSet++;

    return true;
}
