//-- - Day 2: Cube Conundrum-- -

#include "Solutions.h"
struct Colors
{
    int r = 1;
    int g = 1;
    int b = 1;
};

bool CanMatchConfiguration(std::string str);
void GetFewestNumberOfCubesForEachColor(std::string str, Colors* colors);

//Configuration
//12 red cubes, 13 green cubes, and 14 blue cubes
void Solutions::CubeConundrum() // 2239
{
    //Open the File
    std::ifstream fileStream = Utilities::OpenFile("Day 2.txt");

    std::string line;
    long int  sum = 0;
    int currentGame = 1;

    while (std::getline(fileStream, line))
    {
        bool matchesConfiguration = true;
        std::vector<std::string> vec =  Utilities::SplitString(line, ":");
        std::vector<std::string> subSets = Utilities::SplitString(vec[1], ";");
        for(auto subSet : subSets)
        {
            if (!CanMatchConfiguration(subSet))
            {
                matchesConfiguration = false;
            }
        }
        if (matchesConfiguration)
        {
            sum += currentGame;
        }
        ++currentGame;
    }

    std::cout << "Sum of ID's of possible game configurations is " << sum << std::endl;
}


bool CanMatchConfiguration(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); }),
                                str.end());

    std::vector<std::string> config = Utilities::SplitString(str, ",");
    std::regex regex(R"(\d+)"); //matches a sequece on digits
    std::smatch match;

    for (std::string colorString : config)
    {
        std::regex_search(colorString, match, regex);
        int number = std::stoi(match.str());
        if (colorString[1] == 'r' || colorString[2] == 'r') //red
        {
            if (number > 12)
            {
                return false;
            }
        }
        else if ((colorString[1]) == 'g' || colorString[2] == 'g') //green
        {
            if (number > 13)
            {
                return false;
            }
        }
        else //blue
        {
            if (number > 14)
            {
                return false;
            }
        }
    }

    return true;
}


void Solutions::CubeConundrumPartTwo() //83435
{
    //Open the File
    std::ifstream fileStream = Utilities::OpenFile("Cube Conundrum.txt");

    std::string line;
    long int sum = 0;
    int currentGame = 1;

    while (std::getline(fileStream, line))
    {
        bool matchesConfiguration = true;
        std::vector<std::string> vec = Utilities::SplitString(line, ":");
        std::vector<std::string> subSets = Utilities::SplitString(vec[1], ";");
        Colors* colors = new Colors();
        int productOfMinValues = 0;
        for (auto subSet : subSets)
        {
            GetFewestNumberOfCubesForEachColor(subSet, colors);
        }
        sum += colors->r * colors->g * colors->b;
        ++currentGame;
        delete colors;
    }

    std::cout << "Sum of Powers of sets is " << sum << std::endl;
}

//Find the fewest number of cubes of each color that could make the game possible
void GetFewestNumberOfCubesForEachColor(std::string str, Colors* colors) 
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); }),
        str.end());

    std::vector<std::string> config = Utilities::SplitString(str, ",");
    std::regex regex(R"(\d+)"); //matches a sequece on digits
    std::smatch match;

    for (std::string colorString : config)
    {
        std::regex_search(colorString, match, regex);
        int number = std::stoi(match.str());
        int identifier = number < 10 ? 1 : 2;
        if (colorString[identifier] == 'r') //red
        {
            colors->r = number > colors->r ? number : colors->r;
        }
        else if (colorString[identifier] == 'g') //green
        {
            colors->g = number > colors->g ? number : colors->g;
        }
        else //blue
        {
            colors->b = number > colors->b ? number : colors->b;
        }
    }
}
