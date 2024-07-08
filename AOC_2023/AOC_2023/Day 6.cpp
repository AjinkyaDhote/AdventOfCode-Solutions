#include "Solutions.h"

#define sz(x) (int)(x.size()) 

void Solutions::WaitForIt()
{
	std::ifstream fileStream = Utilities::OpenFile("Day 6 Input.txt");

	std::string line;

	std::getline(fileStream, line); //get time values
	std::vector<std::string> timeStringVec = Utilities::ReadSpaceSeperatedString(line);
	
	std::getline(fileStream, line); //get Distance Values
	
	std::vector<std::string> distanceStringVec = Utilities::ReadSpaceSeperatedString(line);
	
	std::map<int, int> inputMap;
	for (int i = 1; i < sz(timeStringVec); i++)
	{
		inputMap[std::stoi(timeStringVec[i])] =  std::stoi(distanceStringVec[i]);
	}

	int ans = 1;
	for (auto &[time, distance] : inputMap)
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