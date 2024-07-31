//Day 13 - Point of Incidence

#include "Solutions.h"

typedef vector<vector<char>> InputMat;

//Wrong answers - 32218, 36118, 35118

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
	if (value == -1)
	{
		InputMat rotated = Rotate(mat, rows, cols);
		value = Process(rotated, cols, rows, true);
		value *= 100;
	}
	
	return value;
}


void Solutions::PointOfIncidence()
{
	ifstream fs = Utilities::OpenFile("Day 13 Input.txt");
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
}