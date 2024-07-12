//--- Day 1: Trebuchet?! ---
#include "Solutions.h"

int CheckIsADigit(std::string subString)
{
    std::string toLower = subString;
    std::transform(subString.begin(), subString.end(), subString.begin(),
        [](unsigned char c) {return std::tolower(c); });

    if (std::strcmp(toLower.c_str(), "one") == 0) return 1;
    else if (std::strcmp(toLower.c_str(), "two") == 0) return 2;
    else if (std::strcmp(toLower.c_str(), "three") == 0) return 3;
    else if (std::strcmp(toLower.c_str(), "four") == 0) return 4;
    else if (std::strcmp(toLower.c_str(), "five") == 0) return 5;
    else if (std::strcmp(toLower.c_str(), "six") == 0) return 6;
    else if (std::strcmp(toLower.c_str(), "seven") == 0)return 7;
    else if (std::strcmp(toLower.c_str(), "eight") == 0) return 8;
    else if (std::strcmp(toLower.c_str(), "nine") == 0) return 9;
    else return -1;
}


void Solutions::SumOfCalibrationValues() //Time - 20 mins - 56465
{
    //Open the File
    std::ifstream fileStream = Utilities::OpenFile("Day1.txt");

    std::string line;
    long int  sum = 0;

    while (std::getline(fileStream, line))
    {
        int firstDigit = -1;
        int lastDigit = -1;
        bool foundFirstDigit = false;
        int number = 0;
        for (char c : line) //Read each line
        {
            if (std::isdigit(c))
            {
                if (!foundFirstDigit)
                {
                    firstDigit = (c - 48);
                    foundFirstDigit = true;
                }
                else
                {
                    lastDigit = (c - 48);
                }
            }
        }

        //Combine the first digit and the last digit to form a number 
        if (!foundFirstDigit)
        {
            //We did not find any digit in the line.
        }
        else if (lastDigit == -1)
        {
            number = firstDigit * 10 + firstDigit; //We only found one digit
        }
        else
        {
            number = firstDigit * 10 + lastDigit; //We found more than one digit
        }

        sum += number; //In the end add all the numbers.
    }

    std::cout << "Day1: Sum of all of the calibration values - " << sum << std::endl;
}

void Solutions::SumOfRealCalibrationValues() //55902 Time - 2hrs
{
    //Open the File
    std::ifstream fileStream = Utilities::OpenFile("Day1.txt");

    std::string line;
    long int  sum = 0;

    while (std::getline(fileStream, line))
    {
        int firstDigit = -1;
        int lastDigit = -1;
        bool foundFirstDigit = false;
        int number = 0;
        bool foundANumber = false;
        std::string subStringForThreeLetters;
        std::string subStringForFourLetters;
        std::string subStringForFiveLetters;
        for (size_t i = 0; i < line.size(); ++i) //Read each line
        {
            //Construct substring as we move ahead in a sliding window fashion.
            char c = line[i];

            if (std::isdigit(c))
            {
                if (!foundFirstDigit)
                {
                    firstDigit = (c - 48);
                    foundFirstDigit = true;
                }
                else
                {
                    lastDigit = (c - 48);
                }
            }
            else
            {
                if ((i + 2) < line.size())
                {
                    subStringForThreeLetters += line[i];
                    subStringForThreeLetters += line[i + 1];
                    subStringForThreeLetters += line[i + 2];
                    int number = CheckIsADigit(subStringForThreeLetters);
                    if (number != -1)
                    {
                        foundANumber = true;
                        if (!foundFirstDigit)
                        {
                            firstDigit = number;
                            foundFirstDigit = true;
                        }
                        else
                        {
                            lastDigit = number;
                        }
                    }
                }
                if (!foundANumber && ((i + 3) < line.size()))
                {
                    subStringForFourLetters += line[i];
                    subStringForFourLetters += line[i + 1];
                    subStringForFourLetters += line[i + 2];
                    subStringForFourLetters += line[i + 3];
                    int number = CheckIsADigit(subStringForFourLetters);
                    if (number != -1)
                    {
                        foundANumber = true;
                        if (!foundFirstDigit)
                        {
                            firstDigit = number;
                            foundFirstDigit = true;
                        }
                        else
                        {
                            lastDigit = number;
                        }
                    }
                }
                if (!foundANumber && (i + 4) < line.size())
                {
                    subStringForFiveLetters += line[i];
                    subStringForFiveLetters += line[i + 1];
                    subStringForFiveLetters += line[i + 2];
                    subStringForFiveLetters += line[i + 3];
                    subStringForFiveLetters += line[i + 4];
                    int number = CheckIsADigit(subStringForFiveLetters);
                    if (number != -1)
                    {
                        if (!foundFirstDigit)
                        {
                            firstDigit = number;
                            foundFirstDigit = true;
                        }
                        else
                        {
                            lastDigit = number;
                        }
                    }
                }
            }
            foundANumber = false;
            subStringForThreeLetters = "";
            subStringForFourLetters = "";
            subStringForFiveLetters = "";
        }

        //Combine the first digit and the last digit to form a number 
        if (!foundFirstDigit)
        {
            //We did not find any digit in the line.
        }
        else if (lastDigit == -1)
        {
            number = firstDigit * 10 + firstDigit; //We only found one digit
        }
        else
        {
            number = firstDigit * 10 + lastDigit; //We found more than one digit
        }

        sum += number; //In the end add all the numbers.
    }

    std::cout << "Day1: Sum of all of the real calibration values - " << sum << std::endl;

    Utilities::CloseFile(fileStream);
}