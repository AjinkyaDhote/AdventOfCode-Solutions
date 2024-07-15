//----- Day 10 - Pipe Maze -----//

#include "Solutions.h"

using namespace std;

typedef vector<vector<char>> InputMat;

struct Node
{
	int x, y;
	string from, to;
};


Node GetStartingDirection(InputMat& maze, int r, int c, int Rows, int Cols)
{
	Node node;

	bool foundValid = false;

	//Find north
	if (r - 1 >= 0)
	{
		char temp = maze[r - 1][c];
		if (temp == '|' || temp == 'F' || temp == '7')
		{
			node.x =  r-1;
			node.y = c;
			node.from = "south";
			node.to = "north";
			foundValid = true;
		}
	}

	//Find east
	if (!foundValid && c + 1 < Cols)
	{
		char temp = maze[r][c + 1];
		if (temp == '-' || temp == 'J' || temp == '7')
		{
			node.x = r;
			node.y = c + 1;
			node.from = "west";
			node.to = "east";
			foundValid = true;	
		}
	}

	//Find south
	if (!foundValid && r + 1 < Rows)
	{
		char temp = maze[r + 1][c];
		if (temp == '|' || temp == '7' || temp == 'F')
		{
			node.x = r + 1;
			node.y = c;
			node.from = "north";
			node.to = "south";
			foundValid = true;
		}
	}


	//Find west
	if (!foundValid && c - 1 >= 0)
	{
		char temp = maze[r][c - 1];
		if (temp == '-' || temp == 'F' || temp == 'L')
		{
			node.x = r;
			node.y = c - 1;
			node.from = "east";
			node.to = "west";
		}
	}

	return node;
}


Node FindNextNodeInLoop(InputMat& maze, Node& node,  int Rows, int Cols)
{
	char north = 0;
	char east = 0;
	char south = 0;
	char west = 0;

	int currentRow = node.x;
	int currentCol = node.y;
	string from = node.from;
	string to = node.to;
	
	char currentChar = maze[currentRow][currentCol];
	
	//if (to == "north")
	//{
	//	switch (currentChar)
	//	{
	//	case '|':
	//		node.x = currentRow - 1;
	//		node.y = currentCol;
	//		node.to = "north";
	//	case '7':
	//		node.x = currentRow;
	//		node.y = currentCol;
	//	case 'F':
	//		
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//else if (to == "east")
	//{
	//	switch (currentChar)
	//	{
	//	case '-':
	//		node.x = currentRow;
	//		node.y = currentCol + 1;
	//		node.to = "east";
	//		break;
	//	case '7':
	//		node.x = currentRow + 1;
	//		node.y = currentCol;
	//		node.to = "south";
	//	case 'J':
	//		node.x = currentRow - 1;
	//		node.y = currentCol;
	//		node.to = "north";
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//else if (to == "south")
	//{
	//	switch (currentChar)
	//	{
	//	case '|':
	//	case 'F':
	//	case '7':
	//		node.x = currentRow + 1;
	//		node.y = currentCol;
	//		break;

	//	default:
	//		break;
	//	}
	//}
	//else if (to == "west")// west
	//{
	//	switch (currentChar)
	//	{
	//	case '-':
	//	case 'J':
	//	case '7':
	//		node.x = currentRow;
	//		node.y = currentCol - 1;
	//		break;
	//	default:
	//		break;
	//	}
	//}

	return node;
}

void Process(InputMat& maze, int startRow, int startCol, int TotalRows, int TotalCols)
{
	stack<char> st;
	int row = startRow;
	int col = startCol;
	bool looped = false;
	Node node = GetStartingDirection(maze, startRow, startCol, TotalRows, TotalCols);
	st.push(maze[node.x][node.y]);
	while (!looped)
	{
		node = FindNextNodeInLoop(maze, node, TotalRows, TotalCols);
		char nextChar = maze[node.x][node.y];
		st.push(nextChar);
	}

}


void Solutions::PipeMaze()
{
	ifstream fs = Utilities::OpenFile("Day 10 Example.txt");

	//Read the map
	string line;

	getline(fs, line);
	int rows = (int)line.size();
	int cols = rows;

	fs.seekg(0);

	InputMat maze(rows, vector<char>(cols));
	int i = 0; int j = 0;
	int startRow = -1, startCol = -1;
	while (getline(fs, line))
	{
		j = 0;
		for (auto& c : line)
		{
			if (c == 'S')
			{
				startRow = i;
				startCol = j;
			}
			maze[i][j] = c;
			j++;
		}
		i++;
	}

	Process(maze, startRow, startCol, rows, cols);
}
