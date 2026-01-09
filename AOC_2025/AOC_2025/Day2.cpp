#include "Solutions2025.h"

namespace AOC_2025
{
    vector<uint64_t> FindInvalidIDs(uint64_t lower, uint64_t upper)
    {
        vector<uint64_t> invalidIDs;
        uint64_t counter = lower;

        //Any id is invalid if it is made only of some sequence of digits repeated twice. //so 55, 123123, 6666. 
        //From the patterns above for an id to be invalid the number of digits in the sequence should be a multiple of 2.
        //If a the sequence is odd the pattern cannot be repeated twice.
        //If not we could just skip the check.

        while (counter <= upper)
        {
            //check number of digits in the sequence is a multiple of 2.
            ostringstream oss;
            oss << counter;
            string temp = oss.str();

           if (temp.length() % 2 == 0)
           {
               size_t mid = temp.length() / 2;

               string other = temp.substr(0, mid);
               temp.erase(0, mid);

               if (other == temp)
                   invalidIDs.push_back(counter);
           }
            counter++;
        }

        return invalidIDs;
    }
  
    void PartOne(vector<string> &ranges)
    {
        uint64_t ans = 0;
        for (uint64_t i = 0; i < ranges.size(); ++i)
        {
            vector<string> rangePair = Utilities::SplitString(ranges[i], "-");
            uint64_t lower = static_cast<uint64_t> (_atoi64(rangePair[0].c_str()));
            uint64_t upper = static_cast<uint64_t> (_atoi64(rangePair[1].c_str()));

            if (lower > upper)
                swap(lower, upper);

            //Find invalid IDs
            auto ids = FindInvalidIDs(lower, upper);
            if (ids.size() == 0) continue;
            cout << "Invalid Ids for Range " << lower << "-" << upper << "\n";
            for (size_t i = 0; i < ids.size(); ++i)
            {
                cout << ids[i] << "\n";
                ans += ids[i];
            }
        }
        cout << "Part One: " << ans;
    }

  //28146997880 

    bool AreCharactersRepeating(string str)
    {
        for (int i = 0; i < str.length() - 1; ++i)
        {
            if (str[i] != str[i + 1])
                return false;
        }
        return true;
    }

    bool AreCharactersRepeating(string str, int interval)
    {
        int i = 0;
        int j = i + interval;
        bool isValid = false;
        while (j + interval <= str.length() && 
            !isValid)
        {
            string tmp1 = str.substr(i, interval);
            string tmp2 = str.substr(j, interval);
            if (tmp1 != tmp2)
                isValid = true;
            i += interval;
            j += interval;
        }
        return !isValid;
    }

    vector<uint64_t> FindInvalidIDs2(uint64_t lower, uint64_t upper)
    {
        vector<uint64_t> invalidIDs;

        uint64_t counter = lower;

        while (counter <= upper)
        {
            ostringstream oss;
            oss << counter;
            string temp = oss.str();
            string pattern = "";
            
            size_t len = temp.length();

            if (len == 1)
            {
                counter++;
                continue;
            }

            if (AreCharactersRepeating(temp))
            {
                invalidIDs.push_back(counter);
                counter++;
                continue;
            }
                
                
            //The only way these total number of digits can have invalid ids is if all digits are equal.
            if (len == 2 || len == 3 || len == 5 || len == 7)
            {
                counter++;
                continue;
            }

            //Get the length of the string
            //Find the multiples of the length. 1 will always be a multiple.
            //Only the multiples can form an invalid number
            //For 4, 6, 8 and 10
            //Multiple of 4 is 2.
            ///Multiples of 6 are 2 and 3
            //Multiples of 8 are 2, 4
            //Multiples of 9 are 3
            //Multiple of 10 are 2, 5
            //So combination of these number of digits can have an invalid ID.

            if (len == 4)
            {
                if (AreCharactersRepeating(temp, 2))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }
            }

            else if (len == 6)
            {
                if (AreCharactersRepeating(temp, 2))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }

                if (AreCharactersRepeating(temp, 3))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }
            }

            else if (len == 8)
            {
                if (AreCharactersRepeating(temp, 2))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }

                if (AreCharactersRepeating(temp, 4))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }
            }

            else if (len == 9)
            {
                if (AreCharactersRepeating(temp, 3))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }
            }

            else if (len == 10)
            {
                if (AreCharactersRepeating(temp, 2))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }

                if (AreCharactersRepeating(temp, 5))
                {
                    invalidIDs.push_back(counter);
                    counter++;
                    continue;
                }
            }
            else
            {
                throw bad_exception();
            }

            counter++;
        }


        return invalidIDs;
        
    }

    void PartTwo(vector<string>& ranges)
    {
        uint64_t ans = 0;
        for (uint64_t i = 0; i < ranges.size(); ++i)
        {
            vector<string> rangePair = Utilities::SplitString(ranges[i], "-");
            uint64_t lower = static_cast<uint64_t>(_atoi64(rangePair[0].c_str()));
            uint64_t upper = static_cast<uint64_t>(_atoi64(rangePair[1].c_str()));

            if (lower > upper)
                swap(lower, upper);

            //Find invalid IDs
            auto ids = FindInvalidIDs2(lower, upper);
            if (ids.size() == 0) continue;
            cout << "Invalid Ids for Range " << lower << "-" << upper << "\n";
            for (size_t i = 0; i < ids.size(); ++i)
            {
                cout << ids[i] << "\n";
                ans += ids[i];
            }
        }
        cout << "Part Two: " << ans;
    }

    void ParseInput()
    {
        std::ifstream fs = Utilities::OpenFile("Day2Input.txt");

        string input;
        vector<string> ranges;
        while (std::getline(fs, input))
        {
            ranges = Utilities::ReadCommaSeperatedString(input);
        }

        //PartOne(ranges);
        PartTwo(ranges);
    }

    void Solutions2025::Day2()
    {
        ParseInput();
    }
}