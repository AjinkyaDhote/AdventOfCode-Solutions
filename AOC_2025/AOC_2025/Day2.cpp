#include "Solutions2025.h"

namespace AOC_2025
{
    vector<int> FindInvalidIDs(int lower, int upper)
    {
        vector<int> invalidIDs;
        int counter = lower;

        //Any id is invalid if it is made only of some sequence of digits repeated twice. //so 55, 123123, 6666. 
        //From the patterns above for an id to be invalid the number of digits in the sequence should be a multiple of 2.
        //If a the sequence is odd the pattern cannot be repeated twice.
        //If not we could just skip the check.

        while (counter <= upper)
        {
            //check number of digits in the sequence is a multiple of 2.
            int count = floor(log10(counter)) + 1;

            if (count % 2 == 0)
            {
                int temp = counter;
                int pattern = 0;
                //Could be an invalid Id. Check if a pattern is repeated twice.
                while (temp > 10)
                {
                    int div = temp / 10;
                    pattern += 10*div;
                    temp = temp % 10;
                    if (temp == pattern)
                        invalidIDs.push_back(counter);
                }
            }
            counter++;
        }

        return invalidIDs;
    }

    void PartOne(vector<string> &ranges)
    {
        long int ans;

        for (int i = 0; i < ranges.size(); ++i)
        {
            vector<string> rangePair = Utilities::SplitString(ranges[i], "-");
            int lower = std::stoi(rangePair[0]);
            int upper = stoi(rangePair[1]);

            //Find invalid IDs
            vector<int> invalidIds = FindInvalidIDs(lower, upper);
            
        }
    }

    void PartTwo()
    {

    }

    void ParseInput()
    {
        std::ifstream fs = Utilities::OpenFile("Day2Example.txt");

        string input;
        vector<string> ranges;
        while (std::getline(fs, input))
        {
            ranges = Utilities::ReadCommaSeperatedString(input);
        }

        PartOne(ranges);
    }

    void Solutions2025::Day2()
    {
        ParseInput();
    }
}