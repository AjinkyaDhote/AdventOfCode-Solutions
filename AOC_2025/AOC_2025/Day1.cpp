#include "Solutions2025.h"

namespace AOC_2025
{
    void Print(std::string input, std::string result);
    void PartOne(ifstream& fs);
    void PartTwo(ifstream& fs);

    void Solutions2025::SecretEntrance()
    {
        ifstream fs = Utilities::OpenFile("Day1Input.txt");
        int ans = 0;
        std::string input;

        PartOne(fs); 
        PartTwo(fs);
    }

    void PartOne(ifstream& fs)
    {
        std::string input;
        int temp = 50; int ans = 0;
        while (std::getline(fs, input))
        {
            int num;
            bool isLeft = input[0] == 'L';
            std::string numStr = Utilities::Ltrim(input, isLeft ? "L" : "R");
            sscanf_s(numStr.c_str(), "%d", &num);
            std::cout << "The dial starts by pointing at " << temp << "\n";
            int counter = 0;
            if (isLeft)
            {
                while (counter != num)
                {
                    temp -= 1;
                    if (temp < 0)
                        temp = abs(100 - abs(temp));
                    counter++;
                }
            }
            else
            {
                while (counter != num)
                {
                    temp += 1;
                    if (temp > 99)
                        temp = 0;
                    counter++;
                }
            }

            Print(isLeft ? "L" + numStr : "R" + numStr, std::to_string(temp));
            if (temp == 0)
                ans++;
        }
        std::cout << "The password is " << ans;
    }

    void PartTwo(ifstream &fs)
    {
        int temp = 50; int ans = 0;
        std::string input;
        std::cout << "The dial starts by pointing at " << temp << "\n";
        while (std::getline(fs, input))
        {
            int num;
            bool isLeft = input[0] == 'L';

            std::string numStr = Utilities::Ltrim(input, isLeft ? "L" : "R");
            sscanf_s(numStr.c_str(), "%d", &num);

            int counter = 0;
            if (isLeft)
            {
                while (counter != num)
                {
                    temp -= 1;
                    if (temp < 0)
                        temp = abs(100 - abs(temp));
                    counter++;
                    if (temp == 0)
                        ans++;
                }
            }
            else
            {
                while (counter != num)
                {
                    temp += 1;
                    if (temp > 99)
                        temp = 0;
                    counter++;
                    if (temp == 0)
                        ans++;
                }
            }

            Print(isLeft ? "L" + numStr : "R" + numStr, std::to_string(temp));
        }
        std::cout << "The password is " << ans;
    }

    void Print(std::string input, std::string result)
    {
        std::cout << "The dial is rotated " <<
            input << " to point at " << result << "\n";
    }
}
