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

uint64_t Calculate(string record, vector<uint64_t> groups);
unordered_map<string, uint64_t> mp;

void Print(string record, vector<uint64_t> groups, uint64_t ret)
{
	std::cout << record << " " << "[";
	for (uint64_t i = 0; i < (uint64_t)groups.size(); i++)
	{
		std::cout << groups[i] << ",";
	}
	std::cout << "] " << "Possible Arrangements: " << ret << "\n";
}

//First character is a dot.
//We skip over the dot to look for the next pound.
//example (record = "...###..", groups=(3,)) --> we skip the dot and recursively call for (record = "..##..", groups=(3,))
uint64_t SolveDot(string record, vector<uint64_t> groups)
{
	string substr = record.substr(1, record.size());
	return Calculate(substr, groups);
}

uint64_t SolvePound(string record, vector<uint64_t> groups, uint64_t nextGroup)
{
	//If first character is #, then the first group number is expected to follow i.e if groups[0] = 3, then the sequence should be ###
	string currentRecord = record.substr(0, nextGroup);
	replace(currentRecord.begin(), currentRecord.end(), '?', '#'); //replace all '?' to '#'

	//if the size of our currentRecord is not equal to next Group, then return 0;
	if (currentRecord.size() != nextGroup) 
		return 0;

	//This sections checks if '#' count in our currentRecord is equal to the next group count.
	//i.e Let currentRecord = "##." and nextGroup = 3, this satisfies the if condition above but is not a valid record
	//We need currentRecord = "###" where count of # is 3, which is a valid record and satisfies our condition.
	{
		uint64_t count = 0;
		size_t pos = currentRecord.find('#', 0);
		while (pos != string::npos)
		{
			pos = currentRecord.find('#', pos + 1);
			count++;
		}

		if (count != nextGroup)
			return 0;
	}
	
	//if rest of the record is just the last group, then we are done and there should only be 
	//one possibility
	if (record.size() == nextGroup)
	{
		//If the groups we are checking is the last group, the we are valid.
		if (groups.size() == 1) //Last Group?
			return 1;

		//There are more groups hence we cannot make it work.
		return 0;
	}

	//The character which follows our valid record must be a '?' or a '.'
	//It will be treated as a separator for our valid current record. After that we find the next record and pass in the next group int.
	if (record[nextGroup] == '?' || record[nextGroup] == '.')
	{
		string substr = record.substr(nextGroup + 1, record.size());
		groups.erase(groups.begin());
		return Calculate(substr, groups);
	}

	return 0;
}

size_t precision = 2; //change the precision with this
size_t hash(const char* str)
{
	return (*(size_t*)str) >> precision;
}

uint64_t Calculate(string record, vector<uint64_t> groups)
{
	string f = record + '|';
	for (auto i : groups)
		f += to_string(i);
	
	if (mp.find(f) != mp.end())
		return mp[f];

	//Base case
	if (groups.empty()) 
		return (record.find('#') == record.npos) ? 1 : 0;

	if (record.empty()) //We have groups but we do not have records to check.
		return 0;

	char nextCharacter = record[0];
	uint64_t nextGroup = groups[0];
	uint64_t ret = 0;
	
	if (nextCharacter == '#')
		ret = SolvePound(record, groups, nextGroup);

	else if (nextCharacter == '.')
		ret = SolveDot(record, groups);

	else if (nextCharacter == '?')
		ret =  SolveDot(record, groups) + SolvePound(record, groups, nextGroup);

	//Print(record, groups, ret);
	mp[f] = ret;
	return ret;
}

void Solutions::Day12()
{
	uint64_t sum = 0, arrangements = 0;
	ifstream fs = Utilities::OpenFile("Day 12 Input.txt");
	string line;

	while (getline(fs, line))
	{
		vector<string> split = Utilities::ReadSpaceSeperatedString(line);
		vector<string> groupsString = Utilities::ReadCommaSeperatedString(split[1]);
		vector<uint64_t > groups;
	
		for (auto numStr : groupsString)
			groups.push_back(stoi(numStr));
	
		arrangements = Calculate(split[0], groups);
		mp.clear();
		//std::cout << split[0] << " " << "[" << split[1] << "] " << "Possible Arrangements: " << arrangements << "\n";
		sum += arrangements;
	}
		
	std::cout << "The sum of different arrangements - " << sum << "\n";

	//https://github.com/crunkyball/AdventOfCode2023/blob/main/Source/Days/Day12.cpp
	std::cout << "\n\n" << "------------------------------------------------------------------------------------------------" << "\n";
	std::cout << "Part Two" << "\n";
	
	mp.clear();
	fs.clear();
	fs.seekg(0);
	line = "";
	sum = 0, arrangements = 0;
	
	while(getline(fs, line))
	{
		vector<string> split = Utilities::ReadSpaceSeperatedString(line);
		vector<string> groupsString = Utilities::ReadCommaSeperatedString(split[1]);
		vector<uint64_t> groups;
		
		string str = "";
		for (uint64_t i = 0; i < 5; ++i)
		{
			for (auto ch : split[0])
				str += ch;
			if (i < 4)
				str += '?';
		}
	
		for (uint64_t  i = 0; i < 5; ++i)
		{
			for (auto numStr : groupsString)
				groups.push_back(stoi(numStr));
		}
	
		arrangements = Calculate(str, groups);
		//Print(str, groups, arrangements);
		mp.clear();
		sum += arrangements;
	}
	
	std::cout << "The sum of different arrangements - " << sum << "\n";

	Utilities::CloseFile(fs);
}