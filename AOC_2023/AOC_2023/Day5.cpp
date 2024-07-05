//------Day 5: If You Give A Seed A Fertilizer----
#include "Solutions.h"

#define DEBUG_TEST


std::vector<std::string> mapTags = {
    "seed-to-soil map:",
    "soil-to-fertilizer map:",
    "fertilizer-to-water map:",
    "water-to-light map:",
    "light-to-temperature map:",
    "temperature-to-humidity map:",
    "humidity-to-location map:"
};


struct Interval
{
    uint64_t source;
    uint64_t destination;
    uint64_t rangeLength;
};


struct Map
{
    std::string name;
    std::vector<Interval> intervals;

    void addInterval(uint64_t sourceStart, uint64_t destinationStart, uint64_t length)
    {
        Interval interval;
        interval.source = sourceStart;
        interval.destination = destinationStart;
        interval.rangeLength = length;
        intervals.push_back(interval);
    }
};


void PartOne(std::ifstream& fs, std::vector<uint64_t> seeds);
void PartTwo(std::ifstream& fs, std::vector<uint64_t> seeds);
uint64_t FindClosestSeedLocation(std::ifstream& fs, std::vector<uint64_t> seeds, bool bPartTwo = false);
uint64_t FindClosestSeedLocation2(std::vector<Map>& maps, std::vector<std::pair<uint64_t, uint64_t>>& inputRanges);

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
    //Convert seeds into inputRange which will be mapped with given maps.
    std::vector<std::pair<uint64_t, uint64_t>> inputRanges;
    for (uint64_t i = 0; i < seeds.size(); )
    {
        inputRanges.push_back({ seeds[i], seeds[i + 1] });
        i = i + 2;
    }

    //Creating Maps
    std::string line;
    std::vector<Map> maps;
    while (std::getline(fs, line))
    {
        if (line.empty())
        {
            continue;
        }
        else
        {
            auto it = std::find(mapTags.begin(), mapTags.end(), line);
            if (it != mapTags.end())
            {
                Map map;
                map.name = *it;
                std::string mapRange;
                std::getline(fs, mapRange);
                while (!mapRange.empty())
                {
                    //Start Reading the map until line is empty
                    std::vector<std::string> values = Utilities::ReadSpaceSeperatedString(mapRange);

                    uint64_t destination = std::stoull(values[0]);
                    uint64_t source = std::stoull(values[1]);
                    uint64_t range = std::stoull(values[2]);
                    map.addInterval(source, destination, range);
                    std::getline(fs, mapRange);
                    if (fs.eof())
                    {
                        std::vector<std::string> values = Utilities::ReadSpaceSeperatedString(mapRange);

                        uint64_t destination = std::stoull(values[0]);
                        uint64_t source = std::stoull(values[1]);
                        uint64_t range = std::stoull(values[2]);
                        map.addInterval(source, destination, range);
                        break;
                    }
                }

                maps.push_back(map);
            }
        }
    }

    std::cout << "The closest location for the given seed numbers is - " << FindClosestSeedLocation2(maps, inputRanges) << "\n";
}

std::pair<uint64_t, uint64_t> Intersection(uint64_t LeftInput, uint64_t RightInput, uint64_t LeftRange, uint64_t RightRange)
{
    if (LeftInput < LeftRange || RightInput > RightRange)
    {
        return { -1, -1 };
    }
    
    return { std::max(LeftInput,LeftRange), std::min(RightInput, RightRange)};
}

uint64_t FindClosestSeedLocation2(std::vector<Map>& maps, std::vector<std::pair<uint64_t, uint64_t>>& inputRanges)
{
    uint64_t ans;

    for (auto& map : maps) //Maps - 7 loops
    {
        std::vector<std::pair<uint64_t, uint64_t>> newInputRanges;

        for (uint64_t i = 0; i < inputRanges.size(); i++)
        {
            std::vector<std::pair<uint64_t, uint64_t>> intersections;

            uint64_t LeftInput = inputRanges[i].first;
            uint64_t RightInput = inputRanges[i].first + inputRanges[i].second - 1;

            
            for (auto& Interval : map.intervals) //Intevals loop
            {
                uint64_t length = Interval.rangeLength;
                uint64_t dest = Interval.destination;
                uint64_t srcStart = Interval.source;
                uint64_t srcEnd = srcStart + length - 1;
    
                std::pair<uint64_t, uint64_t> intersect = Intersection(LeftInput, RightInput, srcStart, srcEnd);
                if (intersect.first != -1 && intersect.second != -1) //Intersection detected
                {
                    //Find the mapping
                    uint64_t mappingStart = dest + intersect.first - srcStart;
                    uint64_t mappingEnd = dest + intersect.second - srcStart;
    
                    newInputRanges.push_back({ mappingStart , mappingEnd });
                    intersections.push_back({ intersect.first, intersect.second });
                }

                //Process non-intersected ranges.
                std::sort(intersections.begin(), intersections.end());
                uint64_t curr = LeftInput;
                for (auto [x, y] : intersections)
                {
                    if (curr < x)
                    {
                        newInputRanges.push_back({ curr, x - 1 });
                    }
                    curr = y + 1;
                }
                if (curr <= RightInput)
                {
                    newInputRanges.push_back({ curr , RightInput });
                }
            }
        }
        inputRanges = newInputRanges;
        
        std::sort(inputRanges.begin(), inputRanges.end());
        ans = std::min(ans, inputRanges[0].first);
    }

    return ans;
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



