//--- Day 8: Haunted Wastelands ---

#include "Solutions.h"
using namespace std;

void ProcessPartOne(string& directions, map<string, pair<string, string>>& nodes)
{
	int directionsLength = (int)directions.size();
	int ptr = 0, counter = 0;
	string out = "";
	string in = "AAA";
	while (out != "ZZZ")
	{
		if (ptr >= directionsLength)
			ptr = 0;

		char direction = directions[ptr];
		auto itr = nodes.find(in);

		auto p = itr->second;
		out = direction == 'L' ? p.first : p.second;
		in = out;

		ptr++;
		counter++;
	}

	std::cout << "Required steps: " << counter << "\n";
}


void ProcessPartTwo(string& directions, map<string, pair<string, string>>& nodes)
{
	int directionsLength = (int)directions.size();
	int ptr = 0, steps = 0;

	//Find all strings that end with "--A"
	vector<string> input;
	for (auto& node : nodes)
	{
		string key = node.first;
		if (key.ends_with('A'))
		{
			input.push_back(key);
		}
	}

	vector<int> allSteps;
	while (allSteps.size() != input.size())
	{
		if (ptr >= directionsLength)
			ptr = 0;
		char direction = directions[ptr];
		vector<string> newInput;
		for (auto& key : input)
		{
			auto itr = nodes.find(key);
			auto p = itr->second;
			string val = direction == 'L' ? p.first : p.second;
			if (val.ends_with('Z'))
			{
				allSteps.push_back(steps + 1);
			}
			newInput.push_back(val);
		}
		ptr++;
		steps++;
		input.clear();
		input = newInput;
	}

	//The trick is to find the LCM of all the paths that reach '--Z' in the end. 
	//First path takes certain steps to reach --Z
	//Second path takes certain steps to reach --Z
	//And so on.

	//Once we find that all paths do reach --Z, to find when they will reach --Z simultaneously we will have 
	//to take the lcm of all the steps. The input is designed in such a way that when brute forced it will take 
	//a lot of time to reach --Z for all paths simultaneously.

	long long int requiredSteps = 1;
	for (auto s : allSteps)
	{
		requiredSteps = lcm(s, requiredSteps);
	}

	std::cout << "Required steps: " << requiredSteps << "\n";
}

void Solutions::HauntedWastelands()
{
	std::cout << "--- Day 8: Haunted Wastelands ---" << "\n\n";

	ifstream fs = Utilities::OpenFile("Day 8 Input.txt");
	string line;
	string instructions = "";
	map<string, pair<string, string>> nodes;

	while (getline(fs, line))
	{
		//ReadInstructions;
		if (instructions.empty())
		{
			instructions = line;
			std::getline(fs, line);//Handle space after
			continue;
		}
			

		vector<string> tokens = Utilities::SplitString(line, "=");
		tokens[0].erase(3); //tokens[0] is the key
		

		vector<string> values = Utilities::ReadCommaSeperatedString(tokens[1]);
		//values [0] is L without the ' ('
		//values [1] is R without the ')'
		string Left = values[0].erase(0,2); 
		values[1].erase(0, 1); //Front space
		values[1].erase(3); //')'
		string Right = values[1];

		nodes[tokens[0]] = { Left, Right };
		//cout << "Key: " << tokens[0] << " Left: " << Left << " Right: " << Right << "\n";
	}


	ProcessPartOne(instructions, nodes);
	ProcessPartTwo(instructions, nodes);

	Utilities::CloseFile(fs);

}