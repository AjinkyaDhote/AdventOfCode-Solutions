#include "Solutions2024.h"

namespace AOC_2024
{
    void PartOne(std::string& str);
    void PartTwo(std::string& str);
    int MultiplyNumbers(std::string& match_str);

    void Solutions2024::MullItOver()
    {
        std::ifstream fs = Utilities::OpenFile("Day3Input.txt");
        std::string str((std::istreambuf_iterator<char>(fs)),
                        (std::istreambuf_iterator<char>()));

        PartOne(str);
        PartTwo(str);
        Utilities::CloseFile(fs);
    }

    void PartOne(std::string& str)
    {
        long long int sum = 0;
        std::regex pattern(R"(mul\((\d+),(\d+)\))");

        auto words_begin = std::sregex_iterator(str.begin(), str.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();

            sum += MultiplyNumbers(match_str);
        }

        std::cout << "Part One - " << sum << '\n';
    }

    int MultiplyNumbers(std::string& match_str)
    {
        //get numbers from the pattern
        std::regex numbersPattern(R"(\d+)");
        auto numbers_begin = std::sregex_iterator(match_str.begin(), match_str.end(), numbersPattern);
        auto numbers_end = std::sregex_iterator();

        int mul = 1;
        while (numbers_begin != numbers_end)
        {
            std::smatch match = *numbers_begin;
            std::string num_str = match.str();
            mul *= stoi(num_str);
            ++numbers_begin;
        }
        return mul;
    }

    void PartTwo(std::string& str)
    {
        long long int sum = 0;
        std::regex pattern(R"(do\(\)|don't\(\)|mul\(\d+,\d+\))");//mul\((\d+),(\d+)\)
        
        auto words_begin = std::sregex_iterator(str.begin(), str.end(), pattern);
        auto words_end = std::sregex_iterator();

        bool ignore = false;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();
            if (match_str == "do()")
                ignore = false;
            else if (match_str == "don't()")
                ignore = true;
            else
            {
                if (!ignore)
                    sum += MultiplyNumbers(match_str);
            }
        }

        std::cout << "Part Two - " << sum << '\n';
    }
}