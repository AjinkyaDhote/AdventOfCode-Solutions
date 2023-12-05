//--- Day 3: Gear Ratios ---

#include "Solutions.h"

typedef std::vector<std::vector<char>> InputMat;
void GearRatiosPartOne(InputMat& mat);

void Solutions::GearRatios()
{
    //Open the File
    std::ifstream fileStream = Utilities::OpenFile("Gear Ratios.txt");
    std::string line;
    long int  sum = 0;

    int rows{ 0 }, columns{ 0 };
    InputMat mat(10, std::vector<char>(10));
    
    while (std::getline(fileStream, line))
    {
        for (size_t j  = 0; j < line.size(); j++)
        {
            mat[rows][j] = line[j];
        }
        ++rows;
    }

    rows = 10;
    columns = 10;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            std::cout << mat[i][j];
        }
        std::cout << "\n";
    }

    GearRatiosPartOne(mat);

}

void GearRatiosPartOne(InputMat& mat) 
{
    //for (no of Rows)
    //{
    //    for (no of cols)
    //    {
    //       //find adjacent elements for that index.
    // 
    //       -if adjacent element is a special character
    //          -we found a part number which needs to be added to the sum
    //          -foundPartNumber = true
    //      
    //      -if (found partNumber jump the cols by the size of the num)
    //
    //    }
    //}
}