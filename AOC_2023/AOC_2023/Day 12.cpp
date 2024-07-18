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

int SolvePartOne(string s, int group)
{
	
	size_t position = s.find('?', 0);
	while (position != s.npos)
	{

	}
		
}


int32_t FindArrangementsForSequence(pair<string, string> spring)
{
	string seq = spring.first;
	string count = spring.second;
	int32_t damaged = 0, operational = 0, unknown = 0;  //damage - '#', operational = '.', unknown = '?'

	for (auto c : seq)
	{
		if (c == '#')
			damaged++;
		else if (c == '.')
			operational++ ;
		else
			unknown++;
	}

	//.??..??...?##. 1,1,3

	//? can either be operational(.) or broken(#)

	//4 unknowns

	



	return -1;


}


void Solutions::Day12()
{
	vector<pair<string, string>> mp;
	int32_t sum = 0;
	ifstream fs = Utilities::OpenFile("Day 12 Example.txt");
	string line;

	while (getline(fs, line))
	{
		vector<string> split = Utilities::ReadSpaceSeperatedString(line);
		mp.push_back({split[0], split[1]});

		
	}

	for (auto& spring : mp)
	{
		int32_t arrangements = FindArrangementsForSequence(spring);
		sum += arrangements;
	}
	
	cout << "The sum of different arrangements - " << sum << "\n";

}