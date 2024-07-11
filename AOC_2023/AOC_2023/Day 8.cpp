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

	cout << "Required steps: " << counter << "\n";
}

void Solutions::HauntedWastelands()
{
	cout << "--- Day 8: Haunted Wastelands ---" << "\n\n";

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
		tokens[0].erase(3);
		//tokens[0] is the key

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

	Utilities::CloseFile(fs);

}