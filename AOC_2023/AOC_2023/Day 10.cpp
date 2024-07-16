//----- Day 10 - Pipe Maze -----//

#include "Solutions.h"

using namespace std;

typedef vector<vector<char>> InputMat;

struct Node
{
	int x = -1, y = -1;
	string from = "", to = "";
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
	int currentRow = node.x;
	int currentCol = node.y;
	string from = node.from;
	string to = node.to;
	
	char currentChar = maze[currentRow][currentCol];
	
	if (to == "north")
	{
		switch (currentChar)
		{
		case '|':
			node.x = currentRow - 1;
			node.y = currentCol;
			node.to = "north";
			break;
		case '7':
			node.x = currentRow;
			node.y = currentCol - 1;
			node.to = "west";
			break;
		case 'F':
			node.x = currentRow;
			node.y = currentCol + 1;
			node.to = "east";
			break;
		default:
			break;
		}
	}
	else if (to == "east")
	{
		switch (currentChar)
		{
		case '-':
			node.x = currentRow;
			node.y = currentCol + 1;
			node.to = "east";
			break;
		case '7':
			node.x = currentRow + 1;
			node.y = currentCol;
			node.to = "south";
			break;
		case 'J':
			node.x = currentRow - 1;
			node.y = currentCol;
			node.to = "north";
			break;
		default:
			break;
		}
	}
	else if (to == "south")
	{
		switch (currentChar)
		{
		case '|':
			node.x = currentRow + 1;
			node.y = currentCol;
			node.to = "south";
			break;
		case 'J':
			node.x = currentRow;
			node.y = currentCol - 1;
			node.to = "west";
			break;
		case 'L':
			node.x = currentRow;
			node.y = currentCol + 1;
			node.to = "east";
			break;

		default:
			break;
		}
	}
	else if (to == "west")// west
	{
		switch (currentChar)
		{
		case '-':
			node.x = currentRow;
			node.y = currentCol - 1;
			node.to = "west";
			break;
		case 'L':
			node.x = currentRow - 1;
			node.y = currentCol;
			node.to = "north";
			break;
		case 'F':
			node.x = currentRow + 1;
			node.y = currentCol;
			node.to = "south";
			break;
		default:
			break;
		}
	}

	return node;
}

bool GetEdgeIntersectionCount(InputMat& maze, vector<pair<int, int>>& edges, int x, int y, int TotalRows, int TotalCols)
{
	//Ray casting algorithm. Shoot a horizontal ray from the point to check how many times it intersets the polygon.
	//If the count is even, the point is outside the polygon. If the count is odd it is inside the polygon.
	int intersectionCount = 0, blockingTiles = 0;
	int nCount = 0, sCount = 0;
	while (y < TotalCols)
	{
		pair<int, int> p{x, y};
		
		if (find(edges.begin(), edges.end(), p)!= edges.end())
		{
			char c = maze[x][y];				
			if (c == '|') { nCount++; sCount++; } //See if we are blocked by north or south pipe and increment them likewise.
			else if (c == 'F' || c == '7')
				sCount++;
			else if (c == 'L' || c == 'J')
				nCount++;
		}
		y++;
	}

	blockingTiles = min(nCount, sCount); //Get the min of north blocking and south blocking pipes
	if (blockingTiles % 2 != 0) //If the count is odd point lies inside, otherwise point lies outside the loop.
		return true;
	return false;
}

void Process(InputMat& maze, Node& startNode, int TotalRows, int TotalCols)
{
	vector<pair <int, int>> edges;
	bool looped = false;

	int startRow = startNode.x;
	int startCol = startNode.y;
	edges.push_back({ startRow, startCol }); //Push back the starting node.

	Node node = GetStartingDirection(maze, startRow, startCol, TotalRows, TotalCols);
	string startDirection = node.to;
	edges.push_back({ node.x, node.y });

	//Part One
	while (!looped)
	{
		node = FindNextNodeInLoop(maze, node, TotalRows, TotalCols);
		char nextChar = maze[node.x][node.y];
		edges.push_back({ node.x, node.y });
		looped = nextChar == 'S';
	}
	
	string endDirection = node.to;

	std::cout << "Steps to reach farthest point from starting position - " << edges.size() / 2 << "\n";


	//Part Two

	//We need to replace 'S' with the right pipe based on where we started and where we ended.
	if ((startDirection == "north") && endDirection == "east")
		maze[startRow][startCol] = 'L';
	else if ((startDirection == "north") && endDirection == "west")
		maze[startRow][startCol] = 'J';
	else if ((startDirection == "south") && endDirection == "west")
		maze[startRow][startCol] = '7';
	else if ((startDirection == "south") && endDirection == "east")
		maze[startRow][startCol] = 'F';
	else if ((startDirection == "north") || (startDirection == "south") &&
		(endDirection == "north") || (endDirection == "south"))
		maze[startRow][startCol] = '|';
	else maze[startRow][startCol] = '-';

	int pointsInsideTheLoop = 0;
	for (int i = 0; i < TotalRows; i++)
	{
		for (int j = 0; j < TotalCols; j++)
		{
			pair<int, int> p{ i, j };
			if (find (edges.begin(), edges.end(), p) != edges.end()) //If we are an edge, skip
				continue;
			if (GetEdgeIntersectionCount(maze, edges, i, j, TotalRows, TotalCols))
				pointsInsideTheLoop++;
		}
	}

	std::cout << "Number of points inside the loop - " << pointsInsideTheLoop << "\n";
}


void Solutions::PipeMaze()
{
	ifstream fs = Utilities::OpenFile("Day 10 Input.txt");

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
	Node startNode;
	startNode.x = startRow;
	startNode.y = startCol;

	Process(maze, startNode, rows, cols);
}
