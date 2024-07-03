//------Day 5: If You Give A Seed A Fertilizer----


#include "Solutions.h"

#define DEBUG_TEST

void PartOne(std::ifstream& fs, std::vector<uint64_t> seeds);
void PartTwo(std::ifstream& fs, std::vector<uint64_t> seeds);
uint64_t FindClosestSeedLocation(std::ifstream& fs, std::vector<uint64_t> seeds, bool bPartTwo = false);
uint64_t FindClosestSeedLocation2(std::ifstream& fs, std::vector<uint64_t> seeds);

std::vector<std::string> mapTags = {
    "seed-to-soil map:",
    "soil-to-fertilizer map:",
    "fertilizer-to-water map:",
    "water-to-light map:",
    "light-to-temperature map:",
    "temperature-to-humidity map:",
    "humidity-to-location map:"
};

struct Range
{
    uint64_t source;
    uint64_t destination;
    uint64_t rangeLength;
}; 


struct Map
{
    std::string name;
    std::vector<Range> ranges;

    void addRange(uint64_t sourceStart, uint64_t destinationStart, uint64_t length)
    {
        Range range;
        range.source = sourceStart;
        range.destination = destinationStart;
        range.rangeLength = length;
    }
};






void Solutions::IfYouGiveASeedAFertilizer()
{
    std::cout << "Day 5 - If You Give A Seed A Fertilizer" << std::endl;

	//Open a stream and read the input
	std::ifstream fs = Utilities::OpenFile("Day 5 Example.txt");
	std::string seedInputLine;

	std::getline(fs, seedInputLine);

	std::vector<std::string> split = Utilities::SplitString(seedInputLine, ":");

	std::vector<std::string> seedsStringVector = Utilities::ReadSpaceSeperatedString(split[1]);

	std::vector<uint64_t> seeds(seedsStringVector.size());

	//We have all the seeds now in seeds vector.
	std::transform(seedsStringVector.begin(), seedsStringVector.end(), seeds.begin(), [](const std::string str) {
		return std::stoul(str); });

    std::cout << "Part One" << "\n";
    //PartOne(fs, seeds);
    
    //Reset the stream pointer to the beginning
    fs.clear();
    fs.seekg(0);

    std::getline(fs, seedInputLine); //getline once to move the stream ahead as we already have the seeds input.

    std::cout << "Part Two" << "\n";
    PartTwo(fs, seeds);
}


void PartOne(std::ifstream& fs, std::vector<uint64_t> seeds)
{
    std::cout << "The closest location for the given seed numbers is - " << FindClosestSeedLocation(fs, seeds) << "\n";
}


void PartTwo(std::ifstream& fs, std::vector<uint64_t> seeds)
{
    
    std::string line;
    //Create map values
    std::string mapName = "";
    while (std::getline(fs, line))
    {
        if (line.empty())
        {
            mapName.clear();
            continue;
        }
        else
        {
            auto it = std::find(mapTags.begin(), mapTags.end(), line);
            if (it != mapTags.end())
            {
                mapName = *it;
                continue;
            }

            
            //Start Reading the map until line is empty
            std::vector<std::string> lineSplit = Utilities::ReadSpaceSeperatedString(line);

            uint64_t destination = std::stoull(lineSplit[0]);
            uint64_t source = std::stoull(lineSplit[1]);
            uint64_t range = std::stoull(lineSplit[2]);
            
        }
    }

    std::cout << "The closest location for the given seed numbers is - " << FindClosestSeedLocation2(fs, seeds) << "\n";
}


uint64_t FindClosestSeedLocation2(std::ifstream& fs, std::vector<uint64_t> seeds)
{
    

    

    return 0;
}


uint64_t FindClosestSeedLocation (std::ifstream& fs, std::vector<uint64_t> seeds, bool bPartTwo)
{
    std::string line;
    bool readingMap = false;
    uint64_t closestLocation = 0;
    std::vector<uint64_t> sourceVector;
    std::unordered_map<uint64_t, uint64_t> mappedValues;
    std::map<uint64_t, uint64_t> sourceToDestinationMap;

    std::copy(seeds.begin(), seeds.end(), std::inserter(sourceVector, sourceVector.end()));

    std::transform(seeds.begin(), seeds.end(), std::inserter(mappedValues, mappedValues.end()), [](uint64_t val)
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

        if (std::find(mapTags.begin(), mapTags.end(), line) != mapTags.end())
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

            uint64_t destination = std::stoull(lineSplit[0]);
            uint64_t source = std::stoull(lineSplit[1]);
            uint64_t sourceRange = std::stoull(lineSplit[2]);

            

            //else
            {
				////Construct an unordered_map which tracks whether the element in source vector is in the range.
				std::unordered_map<uint64_t, bool> inRange;
				for (auto& element : sourceVector)
				{
					if (element >= source && element < source + sourceRange)
					{
						inRange[element] = true;
					}
				}

				// For each element in range find the corresponding mapped value from destination range.
				for (auto& element : inRange)
				{
					uint64_t diff = element.first - source;
					uint64_t mapped = destination + diff;
					sourceToDestinationMap[element.first] = mapped;
				}

				inRange.clear();

				//Build the Current Map from Source To Destination.
				for (auto& entity : sourceVector)
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



