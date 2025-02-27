#include "Solutions2024.h"

namespace AOC_2024
{
    void SolvePartOne(std::vector<int>& firstVector, std::vector<int>& secondVector);
    void SolvePartTwo(std::vector<int>& firstVector, std::vector<int>& secondVector);

    void Solutions2024::HistorianHysteria()
    {
        std::ifstream fs = Utilities::OpenFile("Day1Input.txt");

        std::vector<int> firstVector; std::vector<int> secondVector;

        std::string column;
        while (std::getline(fs, column))
        {
            std::vector<std::string> split = Utilities::ReadSpaceSeperatedString(column);

            firstVector.push_back(std::stoi(split[0]));
            secondVector.push_back(std::stoi(split[1]));
        }

        SolvePartOne(firstVector, secondVector);
        SolvePartTwo(firstVector, secondVector);

        Utilities::CloseFile(fs);
    }

    void SolvePartOne(std::vector<int>& firstVector, std::vector<int>& secondVector)
    {
        std::sort(firstVector.begin(), firstVector.end());
        std::sort(secondVector.begin(), secondVector.end());

        long sum = 0;
        for (int i = 0; i < firstVector.size(); ++i)
        {
            sum += std::abs(firstVector[i] - secondVector[i]);
        }
        std::cout << "Part One " << sum << "\n";
    }

    void SolvePartTwo(std::vector<int>& firstVector, std::vector<int>& secondVector)
    {
        std::unordered_map<int, int> svm;
        
        FOR(i, sz(secondVector))
        {
            if (svm.find(secondVector[i]) != svm.end())
            {
                svm[secondVector[i]]++;
            }
            else
            {
                svm[secondVector[i]] = 1;
            }
        }

        long sum = 0;
        FOR(i, sz(firstVector))
        {
            if (svm.find(firstVector[i]) != svm.end())
            {
                sum += firstVector[i] * svm[firstVector[i]];
            }
            
        }

        std::cout << "Part Two " << sum << "\n";
    }
}