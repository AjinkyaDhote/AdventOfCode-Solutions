#include "Solutions.h"
using namespace std;
#ifndef DEBUG
#define DEBUG
#endif // !DEBUG

typedef vector<vector<char>> InputMat;
typedef pair<int, int> IntPair;
typedef map<int, pair<int, int>> Markers;

void ProcessPartOne(InputMat& mat, Markers& markers)
{
	int sum = 0;
	for (auto it = markers.begin(); it != markers.end(); it++)
	{
		auto temp = next(it,1);
		while (temp != markers.end())
		{
			IntPair one = it->second;
			IntPair two = temp->second;
			int dist = abs(two.first - one.first) + abs(two.second - one.second);
			sum += dist;
			++temp;
		}
	}

	cout << "Part One Sum - " << sum << "\n";

}

void ProcessPartTwo(Markers& markers, vector<int>& rowsExpanded, vector<int>& colsExpanded, int multiplier = 1000000)
{
	long long int sum = 0;
	for (auto it = markers.begin(); it != markers.end(); it++)
	{
		auto temp = next(it, 1);
		while (temp != markers.end())
		{
			IntPair one = it->second;
			IntPair two = temp->second;

			//We need to check how many rows and cols were expanded between these two points.
			int x1 = one.first;
			int x2 = one.second;
			int y1 = two.first;
			int y2 = two.second;

			int rowsAdded = 0, colsAdded = 0;
			for (int rowNumber : rowsExpanded)
			{
				if (min(x1,y1) < rowNumber && rowNumber < max(x1,y1))
					rowsAdded++;
			}
			for (int colNumber : colsExpanded)
			{
				if (min(x2,y2) < colNumber && colNumber < max(x2,y2))
					colsAdded++;
			}


			long long int dist = (long long int)abs(two.first - one.first) + abs(two.second - one.second);
			dist += (long long int)((rowsAdded + colsAdded) * (multiplier - 2)); //One row and one column is already inclusive
			sum += dist;
			++temp;
		}
	}

	cout << "Part Two Sum - " << sum << "\n";
}


void Solutions::CosmicExplosion()
{
	ifstream fs = Utilities::OpenFile("Day 11 Input.txt");
	string line;
	getline(fs, line);
	int rows = (int)line.size();
	int cols = rows;
	vector<int> rowsExpanded;
	vector<int> columnsExpanded;
	fs.seekg(0);

	InputMat mat(rows, vector<char>(cols));
	int index = 0;
	bool found = false;
	Markers markers;
	while (getline(fs, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '#')
			{
				found = true;
			}
			mat[index][i] = line[i];
		}
		
		if (!found)
		{
			mat.resize(mat.size() + 1, vector<char>(cols)); //expand rows
			index++;
			rowsExpanded.push_back(index);
			rows++;
			for (int j = 0; j < cols; j++)
			{
				mat[index][j] = '.';
			}
		}

		index++;
		found = false;
	}

	InputMat expandedMat(rows, vector<char>(cols));
	int extend = 0; //Used to diff the extended columns when accesing older array.
	int j = 0;
	for (; j < cols; j++)
	{
		bool found = false;
		for (int i = 0; i < rows; i++) //expand cols
		{
			if (mat[i][j - extend] == '#')
			{
				found = true;
				expandedMat[i][j] = '#';
				
			}
			else
				expandedMat[i][j] = '.';
		}
		if (!found)
		{
			extend++; cols++; j++;
			columnsExpanded.push_back(j);
			for (int k = 0; k < rows; k++)
			{
				expandedMat[k].resize(expandedMat[k].size() + 1);
				expandedMat[k][j] = '.';
			}
		}
	}

	int count = 0;
	for (int i = 0; i < expandedMat.size(); i++)
	{
		for (int j = 0; j < expandedMat[i].size(); j++)
		{
			if (expandedMat[i][j] == '#')
			{
				markers[++count] = { i, j };
			}
			cout << expandedMat[i][j];
		}
		cout << "\n";
	}


	ProcessPartOne(expandedMat, markers);
	ProcessPartTwo(markers, rowsExpanded, columnsExpanded);
}