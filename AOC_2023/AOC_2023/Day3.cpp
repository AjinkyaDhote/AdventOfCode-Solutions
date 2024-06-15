//--- Day 3: Gear Ratios ---

#include "Solutions.h"

typedef std::vector<std::vector<char>> InputMat;
void GearRatiosPartOne(InputMat& mat);
void GearRatiosPartTwo(InputMat& mat);
bool IsAdjacentElementASpecialCharacter(InputMat& mat, int currentRow, int currentColumn, int TotalRows, int TotalColumns);
//Gear* FindGear(InputMat& mat, int currentRow, int currentColumn, int TotalRows, int TotalColumns);

//struct Gear
//{
//    int partNumberOne = -1;
//    int partNumberTwo = -1;
//    int i = -1;
//    int j = -1;
//    bool foundPartNumberOne = false;
//    bool foundPartNumberTwo = false;
//};

struct Gear
{
    int row, col;
    int partOneNumber, partTwoNumber;
    Gear() : row (-1), col(-1), partOneNumber(-1), partTwoNumber(-1) {}
    Gear(int gearRow, int gearCol) : row(gearRow), col(gearCol) {}

    bool HasBothPartNumbers() const { return partOneNumber != -1 && partTwoNumber != -1; }
};

std::vector<Gear> gearVec;

void Solutions::GearRatios()
{
    //Open the File
    std::ifstream fileStream = Utilities::OpenFile("Gear Ratios.txt");
    std::string line;
    long int  sum = 0;
    std::getline(fileStream, line);
    int rows{ 0 }, columns{ 0 };
    rows = line.size();
    columns = line.size();
    int i = 0;

    InputMat mat(rows, std::vector<char>(columns));

    fileStream.seekg(0, std::ios::beg); //back to the start;

    while (std::getline(fileStream, line))
    {
        for (size_t j  = 0; j < line.size(); j++)
        {
            mat[i][j] = line[j];
        }
        ++i;
    }

	/*for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			std::cout << mat[i][j];
		}
		std::cout << "\n";
	}*/

    GearRatiosPartOne(mat);
    GearRatiosPartTwo(mat);

}

bool FindGear(InputMat& mat, int currentRow, int currentColumn, int TotalRows, int TotalColumns, int &gearRow, int &gearCol)
{
    //Index of Adjacent elements
    char topLeft = '.';
    char top = '.';
    char topRight = '.';
    char midLeft = '.';
    char midRight = '.';
    char bottomLeft = '.';
    char bottom = '.';
    char bottomRight = '.';

    //Top Left
    if (currentRow > 0 && currentColumn > 0)
    {
        topLeft = mat[currentRow - 1][currentColumn - 1];
        if ((!isdigit(topLeft) && topLeft != '.'))
        {
            gearRow = currentRow - 1;
            gearCol = currentColumn - 1;
        }
    }

    if (currentRow > 0)
    {
        top = mat[currentRow - 1][currentColumn];
        if ((!isdigit(top) && top != '.'))
        {
            gearRow = currentRow - 1;
            gearCol = currentColumn;
        }
    }

    //Top Right
    if (currentColumn + 1 < TotalColumns && currentRow > 0)
    {
        topRight = mat[currentRow - 1][currentColumn + 1];
        if ((!isdigit(topRight) && topRight != '.'))
        {
            gearRow = currentRow - 1;
            gearCol = currentColumn + 1;
        }
    }

    //Left
    if (currentColumn > 0)
    {
        midLeft = mat[currentRow][currentColumn - 1];
        if ((!isdigit(midLeft) && midLeft != '.'))
        {
            gearRow = currentRow;
            gearCol = currentColumn - 1;
        }
    }

    //right
    if (currentColumn + 1 < TotalColumns)
    {
        midRight = mat[currentRow][currentColumn + 1];
        if ((!isdigit(midRight) && midRight != '.'))
        {
            gearRow = currentRow;
            gearCol = currentColumn + 1;
        }
    }

    //bottom Left
    if (currentRow < TotalRows - 1 && currentColumn > 0)
    {
        bottomLeft = mat[currentRow + 1][currentColumn - 1];
        if ((!isdigit(bottomLeft) && bottomLeft != '.'))
        {
            gearRow = currentRow + 1;
            gearCol = currentColumn - 1;
        }
    }

    //bottom
    if (currentRow < TotalRows - 1)
    {
        bottom = mat[currentRow + 1][currentColumn];
        if ((!isdigit(bottom) && bottom != '.'))
        {
            gearRow = currentRow + 1;
            gearCol = currentColumn;
        }
    }

    //bottom Right
    if (currentRow < TotalRows - 1 && currentColumn + 1 < TotalColumns) //Bottom Right
    {
        bottomRight = mat[currentRow + 1][currentColumn + 1];
        if ((!isdigit(bottomRight) && bottomRight != '.'))
        {
            gearRow = currentRow + 1;
            gearCol = currentColumn + 1;
        }
    }

    return gearRow != -1 && gearCol != -1;
}

void GearRatiosPartOne(InputMat& mat) // 553079
{
    //TODO : Remove hard coded values
    size_t rows = mat.size();
    size_t cols = mat.size();
    int sum = 0;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols;)
        {
            if (isdigit(mat[i][j]))
            {
                int numStartIndex = j;
                int numEndIndex = j;

                while (numEndIndex < cols)
                {
                    if (numEndIndex + 1 == cols)
                    {
                        //We have reached the last column
                        numEndIndex = numEndIndex + 1;
                        break;
                    }
                    else if (isdigit(mat[i][numEndIndex]))
                    {
                        numEndIndex++;
                    }
                    else
                        break;
                }

                int numLength = (numEndIndex) - numStartIndex; //Get the number Length;
                bool value = false;
                std::string strNum;
                for (; numStartIndex < numEndIndex; ++numStartIndex)
                {
                     strNum += mat[i][numStartIndex];
                     if (!value)
                        value = IsAdjacentElementASpecialCharacter(mat, i, numStartIndex, rows, cols); //Value is already true for elements parsed so skip.
                }
                
                if (value == true)
                {
                    //Form the Part Number and add it to the sum
                    sum += std::stoi(strNum);
                    
                }
                j = numEndIndex;
            }
            else
            {
                ++j;
            }
        }
    }

    std::cout << "The sum of all of the part numbers in engine schematics is " << sum << std::endl;
}

bool IsAdjacentElementASpecialCharacter(InputMat& mat, int currentRow, int currentColumn, int TotalRows, int TotalColumns)
{
    //Index of Adjacent elements
    char topLeft = '.';
    char top = '.';
    char topRight = '.';
    char midLeft = '.';
    char midRight = '.';
    char bottomLeft = '.';
    char bottom = '.';
    char bottomRight = '.';

    //std::cout << "Checking Adjacent Elements for the char " << mat[currentRow][currentColumn] << " at Row - " << currentRow << " and Column - " << currentColumn << std::endl;

    //Top Left
    if (currentRow > 0 && currentColumn > 0)
    {
        topLeft = mat[currentRow - 1][currentColumn - 1];
    }

    //Top
    if (currentRow > 0)
    {
        top = mat[currentRow - 1][currentColumn];
    }

    //Top Right
    if (currentColumn + 1 < TotalColumns && currentRow > 0)
    {
        topRight = mat[currentRow - 1][currentColumn + 1];
    }

    //Left
    if (currentColumn > 0)
    {
        midLeft = mat[currentRow][currentColumn - 1];
    }

    //right
    if (currentColumn + 1 < TotalColumns)
    {
        midRight = mat[currentRow][currentColumn + 1];
    }

    //bottom Left
    if (currentRow < TotalRows - 1 && currentColumn > 0)
    {
        bottomLeft = mat[currentRow + 1][currentColumn - 1];
    }

    //bottom
    if (currentRow < TotalRows - 1)
    {
        bottom = mat[currentRow + 1][currentColumn];
    }

    //bottom Right
    if (currentRow < TotalRows - 1 && currentColumn + 1 < TotalColumns) //Bottom Right
    {
        bottomRight = mat[currentRow + 1][currentColumn + 1];
    }

    if ((!isdigit(topLeft) && topLeft != '.') ||
        (!isdigit(top) && top != '.') ||
        (!isdigit(topRight) && topRight != '.') ||
        (!isdigit(midLeft) && midLeft != '.') ||
        (!isdigit(midRight) && midRight != '.') ||
        (!isdigit(bottomLeft) && bottomLeft != '.') ||
        (!isdigit(bottom) && bottom != '.') ||
        (!isdigit(bottomRight) && bottomRight != '.'))
    {
        return true;
    }

    return false;

}

//A gear is any * symbol that is adjacent to exactly two part numbers.
void GearRatiosPartTwo(InputMat& mat)
{
    size_t rows = mat.size();
    size_t cols = mat.size();
    int sum = 0;
    std::vector<Gear> gears;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols;)
        {
            if (isdigit(mat[i][j]))
            {
                int numStartIndex = j;
                int numEndIndex = j;

                while (numEndIndex < cols)
                {
                    if (numEndIndex + 1 == cols)
                    {
                        //We have reached the last column
                        numEndIndex = numEndIndex + 1;
                        break;
                    }
                    else if (isdigit(mat[i][numEndIndex]))
                    {
                        numEndIndex++;
                    }
                    else
                        break;
                }

                int numLength = (numEndIndex)-numStartIndex; //Get the number length;
                bool value = false;
                std::string strNum;
                int gearRow, gearCol = -1;
                for (; numStartIndex < numEndIndex; ++numStartIndex)
                {
                    strNum += mat[i][numStartIndex];
                    if (!value)
                        value = FindGear(mat, i, numStartIndex, rows, cols, gearRow, gearCol);
                }

                if (value == true)
                {
                    if (gearVec.empty()) //Handle first gear
                    {
                        Gear gear;
                        gear.row = gearRow;
                        gear.col = gearCol;
                        gear.partOneNumber = std::stoi(strNum);
                        gearVec.push_back(gear);
                    }
                    else
                    {
                        //Check if we already know about this gear.
                        bool gearFound = false;
                        for (Gear& g : gearVec)
                        {
                            if (g.HasBothPartNumbers())
                            {
                                //We have both the part Numbers for this gear.
                            }
                            else if (g.partOneNumber != -1 && g.row == gearRow && g.col == gearCol)
                            {
                                //Existing gear. We have the second part number for this gear.
                                g.partTwoNumber = std::stoi(strNum);
                                gearFound = true;
                            }
                        }
                        if (!gearFound) //New gear
                        {
                            Gear gear;
                            gear.row = gearRow;
                            gear.col = gearCol;
                            gear.partOneNumber = std::stoi(strNum);
                            gearVec.push_back(gear);
                        }
                    }
                    
                }
                j = numEndIndex;
            }
            else
            {
                ++j;
            }
        }
    }

    long int gearRatioSum = 0;
    for (const Gear& g : gearVec)
    {
        if (g.HasBothPartNumbers())
        {
            int gearRatio = g.partOneNumber * g.partTwoNumber;
            gearRatioSum += gearRatio;
        }
    }

    std::cout << "The sum of all of gear ratios in engine schematics is " << gearRatioSum << std::endl;
}


