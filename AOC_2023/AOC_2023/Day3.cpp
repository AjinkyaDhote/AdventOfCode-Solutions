//--- Day 3: Gear Ratios ---

#include "Solutions.h"

typedef std::vector<std::vector<char>> InputMat;
void GearRatiosPartOne(InputMat& mat);
bool IsAdjacentElementASpecialCharacter(InputMat& mat, int currentRow, int currentColumn, int TotalRows, int TotalColumns);

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

//A gear is any * symbol that is adjacent to exactly two part numbers.
void GearRatiosPartTwo(InputMat& mat)
{

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
    if (currentColumn + 1  < TotalColumns) 
    {
        midRight = mat[currentRow][currentColumn + 1];
    }
	
    //bottom Left
    if (currentRow < TotalRows - 1  && currentColumn > 0)
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

    if ( (!isdigit(topLeft) && topLeft != '.') ||
         (!isdigit(top) && top != '.') ||
         (!isdigit(topRight) && topRight != '.') ||
         (!isdigit(midLeft) && midLeft != '.') ||
         (!isdigit(midRight) && midRight != '.') ||
         (!isdigit(bottomLeft) && bottomLeft != '.') ||
         (!isdigit(bottom) && bottom != '.') ||
         (!isdigit(bottomRight) && bottomRight != '.') )
    {
        return true;
    }


    return false;

}