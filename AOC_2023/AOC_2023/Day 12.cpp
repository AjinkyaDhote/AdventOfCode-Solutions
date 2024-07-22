#include "Solutions.h"


//You have a bunch of unknown characters("?") where you have two choices, replace it with a "." or replace it with a "#".
// Thus, to compute every possible permutation you would need to make every possible choice.
//
//So to generate all permutations, for the first character, make the choice to make it a ".".
// Then continue on in the string, perhaps recursively, remembering your position.Once you get to another question mark, you make a choice again.
// This continues on until you are at the end of the string, and you have a string with no unknowns.As you come back up the recursive function, 
// you'll need to make the other choice, and continue down the recursion again with that decision.
//
//This will generate all permutations, which will be something like 2unknowns, which is a pretty small number for part 1. 
// There are various ways you can actually compute this and represent your choices, some more efficient than others, but you can likely get away with any approach.


//So the idea is '?' can be replaced with either a '.' or '#' and we then check if the string passed is valid.


using namespace std;

int Calculate(string record, vector<int> groups);

void Print(string record, vector<int> groups, int ret)
{
	cout << record << " " << "[";
	for (int i = 0; i < groups.size(); i++)
	{
		cout << groups[i] << ",";
	}
	cout << "] " << "Possible Arrangements: " << ret << "\n";
}

//First character is a dot.
//We skip over the dot to look for the next pound.
//example (record = "...###..", groups=(3,)) --> we skip the dot and recursively call for (record = "..##..", groups=(3,))
int SolveDot(string record, vector<int> groups)
{
	string substr = record.substr(1, record.size());
	return Calculate(substr, groups);
}

int SolvePound(string record, vector<int> groups, int nextGroup)
{
	//Process '#' andd call SolvePartOne
	//If first character is #, then the first group number is expected to follow i.e if groups[0] = 3, then the sequence should be ###
	string currentRecord = record.substr(0, nextGroup);
	replace(currentRecord.begin(), currentRecord.end(), '?', '#'); //replace all '?' to '#'

	if (currentRecord.size() != nextGroup)
		return 0;

	int count = 0;
	size_t pos = currentRecord.find('#', 0);
	while (pos != string::npos)
	{
		pos = currentRecord.find('#', pos+1);
		count++;
	}
		
	if (count != nextGroup)
		return 0;

	if (record.size() == nextGroup)
	{
		if (groups.size() == 1) //Last Group?
			return 1;

		return 0;
	}

	if (record[nextGroup] == '?' || record[nextGroup] == '.')
	{
		string substr = record.substr(nextGroup + 1, record.size());
		groups.erase(groups.begin());
		return Calculate(substr, groups);
	}

	return 0;
}



int Calculate(string record, vector<int> groups)
{
	//Base case
	if (groups.empty()) 
		return (record.find('#') == record.npos) ? 1 : 0;

	if (record.empty()) //We have groups but we do not have records to check.
		return 0;

	char nextCharacter = record[0];
	int nextGroup = groups[0];
	int ret = 0;
	
	if (nextCharacter == '#')
		ret = SolvePound(record, groups, nextGroup);

	else if (nextCharacter == '.')
		ret = SolveDot(record, groups);

	else if (nextCharacter == '?')
		ret =  SolveDot(record, groups) + SolvePound(record, groups, nextGroup);

	else {/*Invalid*/}
	
	//Print(record, groups, ret);

	return ret;
}

void Solutions::Day12()
{
	vector<pair<string, string>> mp;
	int32_t sum = 0;
	ifstream fs = Utilities::OpenFile("Day 12 Input.txt");
	string line;

	while (getline(fs, line))
	{
		vector<string> split = Utilities::ReadSpaceSeperatedString(line);
		mp.push_back({split[0], split[1]});	
	}

	for (auto& spring : mp)
	{
		vector<string> groupsString = Utilities::ReadCommaSeperatedString(spring.second);
		vector<int> groups;

		for (auto numStr : groupsString)
		{
			groups.push_back(stoi(numStr));
		}
		
		int32_t arrangements = Calculate(spring.first, groups);
		cout << spring.first << " " << "[" << spring.second << "] " << "Possible Arrangements: " << arrangements << "\n";
		sum += arrangements;
	}
	
	cout << "The sum of different arrangements - " << sum << "\n";
	Utilities::CloseFile(fs);
}