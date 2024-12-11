#include "Solutions2024.h"

namespace AOC_2024
{
    void Solutions2024::CeresSearch()
    {
        //Find the position of X.
        //For all it's 8 edges search for M.
        //If found, then alongs all it's edges search for A.
        //If found, then along all it's eges search for S.

        //While doing this check if every position is within the boundaries.


        std::ifstream fs = Utilities::OpenFile("Day4Example.txt");

        std::vector<std::vector<char>> mat;
        int rows, columns;
        //Read each row
        std::string line;
        while (std::getline(fs, line))
        {
            rows = line.size();
            std::vector<char> row;
            for (int i = 0; i < line.size(); i++)
            {
                row.push_back(line[i]);
            }

            mat.push_back(row);
        }

        columns = mat.size();

        PartOne(mat, rows, columns);
    }


    bool IsValidWordFound(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (mat[i][j] == c)
            return true;

        //Search TopLeft
        return IsValidWordFound(mat, i - 1, j - 1, rows, columns, 'M');

        //Search Top
        return IsValidWordFound(mat, i - 1, j, rows, columns, 'M');

        //Search TopRight
        return IsValidWordFound(mat, i - 1, j + 1, rows, columns, 'M');

        //Search Right
        return IsValidWordFound(mat, i, j + 1, rows, columns, 'M');

        //Search Bottom Right
        return IsValidWordFound(mat, i + 1, j + 1, rows, columns, 'M');

        //Search Bottom
        return IsValidWordFound(mat, i + 1, j, rows, columns, 'M');

        //Search Bottom Left
        return IsValidWordFound(mat, i + 1, j - 1, rows, columns, 'M');

        //Search Left
        return IsValidWordFound(mat, i, j - 1, rows, columns, 'M');
    }

    void PartOne(std::vector<std::vector<char>>& mat, int rows, int columns)
    {
        //Find the position of X.
        //For all it's 8 edges search for M.
        //If found, then alongs all it's edges search for A.
        //If found, then along all it's eges search for S.

        //While doing this check if every position is within the boundaries.

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (mat[i][j] == 'X')
                {
                    //Search the edges

                }
            }
        }


    }

}