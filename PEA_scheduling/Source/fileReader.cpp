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

bool FileReader::readWT(std::string path, int setNum, std::vector<Task>& output)
{
    std::fstream file(path, std::fstream::in);

    if (!file || !file.good())
    {
        std::cerr << "Couldn't open file at: " << path.c_str() << std::endl;
        return false;
    }

    const int setSize = /*40;*/  getInstanceSize(file);  // current issue: this shitty file has mutiple spaces between fucking numbers
    int currentSet = 1;

    output.resize(setSize);

    LoadParametersFromInstanec(setSize, file, output);
    currentSet++;

    return true;
}
