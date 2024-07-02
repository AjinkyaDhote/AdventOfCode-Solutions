//------Day 5: If You Give A Seed A Fertilizer----


#include "Solutions.h"

//define DEBUG_TEST


void DayOne();
unsigned long long FindClosestSeedLocation(std::ifstream& fs, std::vector<unsigned long long> seeds);

std::vector<std::string> maps = {
    "seed-to-soil map:",
    "soil-to-fertilizer map:",
    "fertilizer-to-water map:",
    "water-to-light map:",
    "light-to-temperature map:",
    "temperature-to-humidity map:",
    "humidity-to-location map:"
};

void Solutions::IfYouGiveASeedAFertilizer()
{
    std::cout << "Day 5 - If You Give A Seed A Fertilizer" << std::endl;

     DayOne();

}


void DayOne()
{
    //Open a stream and read the input
    std::ifstream fs = Utilities::OpenFile("Day 5 Input.txt");
    std::string seedInputLine;

    std::getline(fs, seedInputLine);

    std::vector<std::string> split = Utilities::SplitString(seedInputLine, ":");

    std::vector<std::string> seedsStringVector = Utilities::ReadSpaceSeperatedString(split[1]);

    std::vector<unsigned long long> seeds(seedsStringVector.size());

    //We have all the seeds now in seeds vector.
    std::transform(seedsStringVector.begin(), seedsStringVector.end(), seeds.begin(), [](const std::string str) {
        return std::stoul(str); });

    std::cout  << "The closest location for the given seed numbers is - " << FindClosestSeedLocation(fs, seeds) << std::endl;
}

unsigned long long FindClosestSeedLocation (std::ifstream& fs, std::vector<unsigned long long> seeds)
{
    std::string line;
    bool readingMap = false;
    unsigned long long closestLocation = 0;
    std::vector<unsigned long long> sourceVector;
    std::unordered_map<unsigned long long, unsigned long long > mappedValues;
    std::map<unsigned long long, unsigned long long> sourceToDestinationMap;

    std::copy(seeds.begin(), seeds.end(), std::inserter(sourceVector, sourceVector.end()));

    std::transform(seeds.begin(), seeds.end(), std::inserter(mappedValues, mappedValues.end()), [](unsigned long long val) 
        { return std::make_pair(val, val); });

    while (std::getline(fs,line))
    {
        if (line.empty())
        {
           
            readingMap = false;

#ifdef DEBUG_TEST
            std::cout << "\n";
            //Print out mapped Values
            for (auto& source : mappedValues)
                std::cout << source.first << " -> " << source.second << "\n";
#endif 

            sourceVector.clear();

            //Create new Source Vector
            for (auto &source : mappedValues)
            {
                sourceVector.push_back(source.second);
            }
            mappedValues.clear();
            sourceToDestinationMap.clear();
            continue;
        }

        if (std::find(maps.begin(), maps.end(), line) != maps.end())
        {
#ifdef DEBUG_TEST
            //This is the start of map
            std::cout << "\n";
            std::cout << "Reading " << line;
#endif
            readingMap = true;
            continue;
        }

        if (readingMap)
        {
            //We have input from a map. Read destination - source - target values

            std::vector<std::string> lineSplit = Utilities::ReadSpaceSeperatedString(line);

            unsigned long long destination = std::stoull(lineSplit[0]);
            unsigned long long source = std::stoull(lineSplit[1]);
            unsigned long long range = std::stoull(lineSplit[2]);

            ////Construct an unordered_map which tracks whether the element in source vector is in the range.
            std::unordered_map<unsigned long long, bool> inRange;
            for (auto& element : sourceVector)
            {
                if (element >= source && element <= source + range)
                {
                    inRange[element] = true;
                }
            }

            // For each element in range find the corresponding mapped value from destination range.
            for (auto& element : inRange)
            {
                unsigned long long diff = element.first - source;
                unsigned long long mapped = destination + diff;
                sourceToDestinationMap[element.first] = mapped;
            }
            
            inRange.clear();
            
            //Build the Current Map from Source To Destination.
            for (auto &entity : sourceVector)
            {
                if (sourceToDestinationMap.find(entity) != sourceToDestinationMap.end())
                {
                    //We have a mapped value
                    mappedValues[entity] = sourceToDestinationMap[entity];
                }
                else
                {
                    mappedValues[entity] = entity;
                }
            }
        }
    }


    //Find the closest location from the mapped values
    for (const auto &element : mappedValues)
    {
        if (closestLocation == 0)
        {
            closestLocation = element.second;
        }
        else
        {
            closestLocation = std::min(closestLocation, element.second);
        }
    }

    return closestLocation;

}



