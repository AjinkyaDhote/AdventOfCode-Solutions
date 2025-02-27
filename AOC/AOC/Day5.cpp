#include "Solutions2024.h"

namespace AOC_2024
{
	void Solutions2024::PrintQueue()
	{
		ifstream fs = Utilities::OpenFile("Day5Example.txt");

		vector<std::pair<int, int>> rules;
		vector<vector<int>> updates;

		string line;
		while (std::getline(fs, line))
		{
			if (line.find('|', 0) != string::npos)
			{
				std::vector<string> split = Utilities::SplitString(line, "|");
				rules.push_back(make_pair(stoi(split[0]), stoi(split[1])));
				
			}
			else if (line.empty())
			{ }
			else
			{
				std::vector<string> split = Utilities::SplitString(line, ",");
				std::vector<int> update;
				for (size_t i = 0; i < split.size(); ++i)
				{
					update.push_back(stoi(split[i]));
				}
				updates.push_back(update);
			}

		}
	}

	void SolvePartOne()
	{

	}

}