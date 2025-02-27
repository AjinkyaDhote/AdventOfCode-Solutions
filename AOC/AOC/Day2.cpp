#include "Solutions2024.h"

namespace AOC_2024
{
    bool IsReportSafe(std::vector<int>& vec);
    bool IsReportSafeForReal(std::vector<int>& vec);

    void Solutions2024::RedNosedReports()
    {
        std::ifstream fs = Utilities::OpenFile("Day2Input.txt");
        std::vector<int> level;
        int safeReports = 0;
        int actualSafeReports = 0;
        std::string l;
        while (std::getline(fs, l))
        {
            std::vector<std::string> split = Utilities::ReadSpaceSeperatedString(l);

            for (std::string s:split)
            {
                level.push_back(std::stoi(s));
            }

            if (IsReportSafe(level))
            {
                ++safeReports;
            }

            if (IsReportSafeForReal(level))
            {
                ++actualSafeReports;
            }

            level.clear();
        }

        std::cout << "Part One - Safe Reports: " << safeReports << "\n";
        std::cout << "Part Two - Actual Safe Reports: " << actualSafeReports << "\n";
        Utilities::CloseFile(fs);
    }

    bool IsReportSafe(std::vector<int>& vec)
    {
        bool increasing = false, decreasing = false;
        for (int i = 0; i < vec.size() - 1 ; i++)
        {
            int j = i + 1;
            if (std::abs(vec[i] - vec[j]) > 3)
                return false;
            else if (vec[i] == vec[j])
                return false;

            //check change
            if (vec[i] < vec[j])
                increasing = true;
            else
                decreasing = true;

            if (increasing && decreasing)
                return false;
        }

        return true;
    }

    bool IsReportSafeForReal(std::vector<int>& vec)
    {
        bool increasing = false, decreasing = false, unsafe = false;
        for (int i = 0; i < vec.size() - 1; i++)
        {
            int j = i + 1;
            if (std::abs(vec[i] - vec[j]) > 3)
                unsafe = true;
            else
            {
                //check change
                if (vec[i] == vec[j])
                    unsafe = true;
                else if (vec[i] < vec[j])
                    increasing = true;
                else
                    decreasing = true;

                if (increasing && decreasing)
                    unsafe = true;
            }

            if (unsafe)
            {
                //Create a new vector by removing i and check safety
                std::vector<int> newVec = vec;
                newVec.erase(newVec.begin()  + i);
                if (IsReportSafe(newVec))
                    return true;

                //Create a new vector by removing j and check safety
                newVec.clear();
                newVec = vec;
                newVec.erase(newVec.begin() + j);
                if (IsReportSafe(newVec))
                    return true;

                //Edge case: Check if removing the previous element makes the level safe.
                if (i > 0)
                {
                    newVec.clear();
                    newVec = vec;
                    newVec.erase(newVec.begin() + i-1);
                    if (IsReportSafe(newVec))
                        return true;
                }

                return false;
            }
        }

        return true;
    }
}