//Day 13 - Point of Incidence

#include "Solutions.h"

typedef vector<vector<char>> InputMat;

//Wrong answers - 32218

int FindPointOfIncidence(InputMat& mat, int rows, int cols)
{
	//Check vertical
	int x, y = -1;
	bool verticalReflectionFound = false, horizontalReflectionFound = false, perfectReflection = false; //it is perfect reflection if one of the edges is included.

	for (int col = 0; col < cols; col++)
	{
		if (perfectReflection)
			break;
		int colIter = col + 1;
		while (colIter < cols)
		{
			if (perfectReflection)
				break;
			bool found = true;
			for(int i = 0; i < rows; i++)
			{
				if (mat[i][col] != mat[i][colIter])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				int front = col - 1;
				int back = colIter + 1;
				//We found two columns which are identical and the reflection line might be between them.
				//To check this we now move both the cols in opposite direction till we reach the edge.
				//If edge is detected than this is a valid mirror. Otherwise we continue.
				bool perfect = true;
				while (front >= 0 && back < cols)
				{
					for (int i = 0; i < rows; i++)
					{
						if (mat[i][front] != mat[i][back])
						{
							perfect = false;
							break;
						}
					}
					if (!perfect || front == 0 || back == cols)
						break;
					front--;
					back++;
				}
				if ((col == 0 || colIter == cols - 1) ||
				(perfect && (front == 0 || back == cols)))
				{
					x = col;
					y = colIter;
					perfectReflection = true;
					verticalReflectionFound = true;
				}
			}
			col++;
			colIter++;
		}
	}

	if (!perfectReflection)//check horizontal
	{
		for (int row = 0; row < rows; row++)
		{
			if (perfectReflection)
				break;
			int rowIter = row + 1;
			while (rowIter < rows)
			{
				if (perfectReflection)
					break;
				bool found = true;
				for (int j = 0; j < cols; j++)
				{
					if (mat[row][j] != mat[rowIter][j])
					{
						found = false;
						break;
					}
				}
				if (found)
				{
					int front = row - 1;
					int back = rowIter + 1;
					//We found two rows which are identical and the reflection line might be between them.
					//To check this we now move both the rows in opposite direction till we reach the edge.
					//If edge is detected than this is a valid mirror. Otherwise we continue.
					bool perfect = true;
					while (front >= 0 && back < rows)
					{
						for (int j = 0; j < cols; j++)
						{
							if (mat[front][j] != mat[back][j])
							{
								perfect = false;
								break;
							}
						}
						if (!perfect || front == 0 || back == cols)
							break;
						front--;
						back++;
					}
					if ((row == 0 || rowIter == rows - 1) ||
					(perfect && (front == 0 || back == rows)))
					{
						x = row;
						y = rowIter;
						perfectReflection = true;
						horizontalReflectionFound = true;
					}
				}
				row++;
				rowIter++;
			}
		}
	}

	
	if (verticalReflectionFound && perfectReflection) return y; //Find num of cols before the reflection	
	else if (horizontalReflectionFound && perfectReflection) return y * 100; //Find num of rows before the reflection
	
	return 0;
}


void Solutions::PointOfIncidence()
{
	ifstream fs = Utilities::OpenFile("Day 13 Example.txt");
	string line = "";

	InputMat mat;
	vector<char> colVector;
	int rows, cols, sum = 0;

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