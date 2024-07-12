#include "Solutions.h"

using namespace std;


pair<int32_t, int32_t> Process(vector<int32_t> history)
{
	pair<int32_t, int32_t> ret{ 0,0 };
	vector < vector<int32_t>> sequences;
	sequences.push_back(history);
	vector<int32_t> mainSequence = history;
	vector<int32_t> subSequence;
	subSequence.reserve(mainSequence.size() - 1);

	bool found = false;

	while (!found)
	{
		found = true;
		subSequence.reserve(mainSequence.size() - 1);
		for (int32_t i = 0; i < (int32_t)mainSequence.size() - 1; i++)
		{
			int32_t value = mainSequence[i + 1] - mainSequence[i];
			found = value == 0;
			subSequence.push_back(value);
		}
		mainSequence.clear();
		mainSequence = subSequence;
		sequences.push_back(subSequence);
		subSequence.clear();
	}

	
	for (auto& seq : sequences)
	{
		ret.first += *(seq.end() - 1);
	}
	
	
	for (int i = sequences.size() - 1; i >= 0; i--)
	{
		ret.second = sequences[i][0] - ret.second;
	}
	
	return ret;
}



void Solutions::MirageMaintenance()
{
	vector<int32_t> history;

	ifstream fs = Utilities::OpenFile("Day 9 Input.txt");

	string line;
	pair<int32_t, int32_t> ans;
	pair<int32_t, int32_t> ret;
	while (getline(fs, line))
	{
		vector<string> nums = Utilities::ReadSpaceSeperatedString(line);

		for (auto& num : nums)
		{
			history.push_back(stoi(num));
		}
		ret = Process(history);
		ans.first += ret.first;
		ans.second += ret.second;
		history.clear();
	}

	cout << "Sum of extrapolated values for Part One: " << ans.first << "\n";
	cout << "Sum of extrapolated values for Part Two: " << ans.second << "\n";
}