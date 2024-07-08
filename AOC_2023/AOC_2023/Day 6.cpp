#include "Solutions.h"

void PartOne(std::vector<std::pair<int, int>> inputMap)
{
	int ans = 1;
	for (auto& [time, distance] : inputMap)
	{
		int counter = 0;
		int counterBR = 0;
		while (counter <= time)
		{
			if (counter * ((time - counter)) > distance)
			{
				counterBR++;
			}
			counter++;
		}
		ans *= counterBR;
	}

	std::cout << "Answer - " << ans << "\n";
}

void PartTwo(std::vector<std::pair<int, int>>& inputMap)
{
	std::string timeStr = "", distStr = "";
	int times = 1;
	for (auto& [t, d] : inputMap)
	{
		timeStr += std::to_string(t);
		distStr += std::to_string(d);
	}

	uint64_t time = std::stoull(timeStr), dist = std::stoull(distStr);

	
	uint64_t ans = 1;

	int counter = 0;
	int counterBR = 0;
	while (counter <= time)
	{
		if (counter * ((time - counter)) > dist)
		{
			counterBR++;
		}
		counter++;
	}
	ans *= counterBR;

	std::cout << "Answer - " << ans << "\n";
}

void PartOptimized(std::vector<std::pair<int, int>> inputMap) //Constant Time
{
	std::string timeStr = "", distStr = "";
	int times = 1;
	for (auto& [t, d] : inputMap)
	{
		timeStr += std::to_string(t);
		distStr += std::to_string(d);
	}

	long long int time = std::stoull(timeStr), dist = std::stoull(distStr);

	long long int ans = 1;
	{
		long long int a = 1, b = -time, c = dist;

		long double first =  -b - (std::sqrt(b * b - 4 * a * c)) / 2 * a;
		long double second = -b + (std::sqrt(b * b - 4 * a * c)) / 2 * a;

		long long int L = (long long int)first + 1;
		long long int R = (long long int)second;
		long long int ways = (R - L + 1);
		ans *= ways;
	}

	std::cout << "Optimized Solution - Constant Time " << ans << "\n";

}


void Solutions::WaitForIt()
{
	std::ifstream fileStream = Utilities::OpenFile("Day 6 Input.txt");

	std::string line;

	std::getline(fileStream, line); //get time values
	std::vector<std::string> timeStringVec = Utilities::ReadSpaceSeperatedString(line);
	
	std::getline(fileStream, line); //get Distance Values
	
	std::vector<std::string> distanceStringVec = Utilities::ReadSpaceSeperatedString(line);
	
	std::vector<std::pair<int, int>> inputMap;
	
	for (int i = 1; i < sz(timeStringVec); i++)
	{
		inputMap.push_back({ std::stoi(timeStringVec[i]), std::stoi(distanceStringVec[i]) });
	}

	PartOne(inputMap);
	PartTwo(inputMap);

	PartOptimized(inputMap);
}

