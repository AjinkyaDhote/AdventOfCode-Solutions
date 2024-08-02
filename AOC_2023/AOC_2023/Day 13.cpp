//Day 13 - Point of Incidence

#include "Solutions.h"

typedef vector<vector<char>> InputMat;

//Wrong answers - 32218, 36118, 35118

enum ReflectionType
{
	VerticalReflection = 0,
	HorizontalReflection = 1
};



map<int, pair<int, int>> reflections;
map<int, ReflectionType> reflectionType;
int reflectionsCounter = 0;


int Process(InputMat& mat, int rows, int cols, bool rotated = false)
{
	//Check vertical
	int x, y = -1;
	bool perfectReflection = false; //it is perfect reflection if one of the edges is included.
	for (int col = 0; col < cols - 1; col++)
	{
		int colIter = col + 1;
		bool equal = true;

		for (int row = 0; row < rows; row++)
		{
			if (mat[row][col] != mat[row][colIter])
			{
				equal = false;
				break;
			}
		}

		if (equal)
		{
			if (col == 0 || colIter == cols) //we have the edge
			{
				x = col;
				y = colIter;
				perfectReflection = true;
				reflections.insert_or_assign(reflectionsCounter, make_pair(x, y));
				break;
			}

			int colfront = col - 1;
			int colback = colIter + 1;
			bool same = true;
			while (colfront >= 0 && colback < cols)
			{
				for (int row = 0; row < rows; row++)
				{
					if (mat[row][colfront] != mat[row][colback])
					{
						same = false;
						break;
					}
				}
				if (same)
				{
					colfront--;
					colback++;
				}
				else break;
			}
			if (same && (colfront == -1 || colback == cols))
			{
				x = col;
				y = colIter;
				perfectReflection = true;
				reflections.insert_or_assign(reflectionsCounter, make_pair(x, y));
				break;
			}
		}
	}

	if (rotated)
	{
		int ret = cols - y;
		return ret;
	}

	return y;
}

InputMat Rotate(InputMat& mat, int rows, int cols)
{
	InputMat rotated;

	for (int i = 0; i < cols; i++)
	{
		vector<char> temp;
		for (int j = rows - 1; j  >= 0; j--)
			temp.push_back(mat[j][i]);

		rotated.push_back(temp);
	}

	return rotated;
}

int FindPointOfIncidence(InputMat& mat, int rows, int cols)
{
	int value = Process(mat, rows, cols);
	reflectionType[reflectionsCounter] = ReflectionType::VerticalReflection;
	if (value == -1)
	{
		InputMat rotated = Rotate(mat, rows, cols);
		value = Process(rotated, cols, rows, true);
		value *= 100;
		reflectionType[reflectionsCounter] = ReflectionType::HorizontalReflection;
	}
	
	reflectionsCounter++;
	return value;
}


pair<int, int> FindSmudgeVertical(InputMat &mat, int rows, int cols, int rcIndex)
{
	//Check vertical
	int x, y = -1;
	int smudgeCount = 0;
	pair<int, int> smudge{ -1, -1 };
	for (int col = 0; col < cols - 1; col++)
	{
		int colIter = col + 1;

		pair<int, int> p = reflections[rcIndex];
		if (p.first == col && p.second == colIter)//We already know about this reflection so continue.
			continue;

		bool equal = true;

		for (int row = 0; row < rows; row++)
		{
			if (mat[row][col] != mat[row][colIter])
			{
				equal = false;
				smudgeCount++;
				if (smudgeCount > 1)
					break;
			}
		}

		if (smudgeCount == 1) //Find the smudge
		{
			if (col == 0 || colIter == cols) //we have the edge
			{
				x = col;
				y = colIter;
				break;
			}

			int colfront = col - 1;
			int colback = colIter + 1;
			bool same = true;
			while (colfront >= 0 && colback < cols)
			{
				for (int row = 0; row < rows; row++)
				{
					if (mat[row][colfront] != mat[row][colback])
					{
						same = false;
						break;
					}
				}
				if (same)
				{
					colfront--;
					colback++;
				}
				else break;
			}
			if (same && (colfront == -1 || colback == cols))
			{
				x = col;
				y = colIter;
				break;
			}
		}
	}

	if (x == -1 && y == -1)
		return make_pair(-1, -1);

	return make_pair(x, y);
}

pair<int, int> FindSmudgeHorizontal(InputMat& mat, int rows, int cols, int rcIndex)
{
	//Check vertical
	int x = -1, y = -1;
	int smudgeCount = 0;
	pair<int, int> smudge{ -1, -1 };
	for (int row = 0; row < rows - 1; row++)
	{
		int rowIter = row + 1;

		pair<int, int> p = reflections[rcIndex];
		if (p.first == row && p.second == rowIter)//We already know about this reflection so continue.
			continue;

		bool equal = true;

		for (int col = 0; col < cols; col++)
		{
			if (mat[row][col] != mat[rowIter][col])
			{
				equal = false;
				smudgeCount++;
				if (smudgeCount > 1)
					break;
			}
		}

		if (smudgeCount == 1) //Find the smudge
		{
			if (row == 0 || rowIter == rows) //we have the edge
			{
				x = row;
				y = rowIter;
				break;
			}

			int rowfront = row - 1;
			int rowback = rowIter + 1;
			bool same = true;
			while (rowfront >= 0 && rowback < rows)
			{
				for (int col = 0; col < cols; col++)
				{
					if (mat[rowfront][col] != mat[rowback][rowback])
					{
						same = false;
						break;
					}
				}
				if (same)
				{
					rowfront--;
					rowback++;
				}
				else break;
			}
			if (same && (rowfront == -1 || rowback == rows))
			{
				x = row;
				y = rowIter;
				break;
			}
		}
	}

	if (x == -1 && y == -1)
		return make_pair(-1, -1);

	return make_pair(x, y);
}

int FindNewReflection(InputMat &mat, int rows, int cols, int oldX, int oldY, ReflectionType rt, int rcIndex)
{
	//Apart from the old reflection there is a new perfect reflection which is broken due to one character being different(smudge)
	//OldX and OldY from the params list denote the old reflection, Ignore this.
	int ret = -1;

	if (rt == 0) //Current Reflection is vertical
	{	
		pair<int, int> p = FindSmudgeVertical(mat, rows, cols , rcIndex);
		ret = p.second;
	}
	
	//Rotate as there could be a horizontal smudge reflection
	if (ret == -1)
	{
		pair<int, int> p = FindSmudgeHorizontal(mat, rows , rows, rcIndex);
		ret = p.second * 100;
	}

	return ret;
}


void Solutions::PointOfIncidence()
{
	ifstream fs = Utilities::OpenFile("Day 13 Example.txt");
	string line = "";

	InputMat mat;
	vector<char> colVector;
	int rows = 0, cols = 0, sum = 0;

	while (getline(fs, line))
	{
		if (line == "")
		{
			rows = (int)mat.size();
			sum += FindPointOfIncidence(mat, rows, cols);
			mat.clear();
		}
		else
		{
			for (int i = 0; i < line.size(); i++)
			{
				colVector.push_back(line[i]);
			}
			mat.push_back(colVector);
			cols = (int)colVector.size();
			colVector.clear();
		}
	}
	rows = (int)mat.size();
	sum += FindPointOfIncidence(mat, rows, cols);
	cout << "Summary of all notes - " << sum << "\n";


	//Part Two
	fs.clear();
	fs.seekg(0);
	reflectionsCounter = 0, sum = 0, mat.clear(), colVector.clear();
	while (getline(fs, line))
	{
		if (line == "")
		{
			rows = (int)mat.size();
			pair<int, int> p = reflections[reflectionsCounter];
			ReflectionType rt = reflectionType[reflectionsCounter];
			sum += FindNewReflection(mat, rows, cols, p.first, p.second, rt, reflectionsCounter);
			mat.clear();
		}
		else
		{
			for (int i = 0; i < line.size(); i++)
			{
				colVector.push_back(line[i]);
			}
			mat.push_back(colVector);
			cols = (int)colVector.size();
			colVector.clear();
		}
	}

	rows = (int)mat.size();
	pair<int, int> p = reflections[reflectionsCounter];
	ReflectionType rt = reflectionType[reflectionsCounter];
	sum += FindNewReflection(mat, rows, cols, p.first, p.second, rt, reflectionsCounter);
	cout << "Summary of all notes for Part Two - " << sum << "\n";
}