#include "Solutions2024.h"

namespace AOC_2024
{

    void PartOne(std::vector<std::vector<char>>& mat, int rows, int columns);
    void PartTwo(std::vector<std::vector<char>>& mat, int rows, int columns);

    void Solutions2024::CeresSearch()
    {
        std::ifstream fs = Utilities::OpenFile("Day4Input.txt");

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

        //PartOne(mat, rows, columns);
        PartTwo(mat, rows, columns);
    }


    bool TopLeft(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return TopLeft(mat, i - 1, j - 1, rows, columns, toSearch);
        }

        return false;
    }

    bool Top(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return Top(mat, i - 1, j, rows, columns, toSearch);
        }

        return false;
    }

    bool TopRight(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return TopRight(mat, i - 1, j + 1, rows, columns, toSearch);
        }

        return false;
    }

    bool Right(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return Right(mat, i, j + 1, rows, columns, toSearch);
        }
        return false;
    }

    bool BottomRight(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return BottomRight(mat, i + 1, j + 1, rows, columns, toSearch);
        }
        return false;
    }

    bool Bottom(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return Bottom(mat, i + 1, j, rows, columns, toSearch);
        }
        return false;
    }

    bool BottomLeft(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return BottomLeft(mat, i + 1, j - 1, rows, columns, toSearch);
        }
        return false;
    }

    bool Left(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return Left(mat, i, j - 1, rows, columns, toSearch);
        }
        return false;
    }

    int IsValidWordFound(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i > rows || j < 0 || j > columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch;
            if (c == 'M')
                toSearch = 'A';
            else if (c == 'A')
                toSearch = 'S';

            //Search TopLeft
            IsValidWordFound(mat, i - 1, j - 1, rows, columns, toSearch);

            //Search Top
            IsValidWordFound(mat, i - 1, j, rows, columns, toSearch);

            //Search TopRight
            IsValidWordFound(mat, i - 1, j + 1, rows, columns, toSearch);

            //Search Right
            IsValidWordFound(mat, i, j + 1, rows, columns, toSearch);

            //Search Bottom Right
            IsValidWordFound(mat, i + 1, j + 1, rows, columns, toSearch);

            //Search Bottom
            IsValidWordFound(mat, i + 1, j, rows, columns, toSearch);

            //Search Bottom Left
            IsValidWordFound(mat, i + 1, j - 1, rows, columns, toSearch);

            //Search Left
            IsValidWordFound(mat, i, j - 1, rows, columns, toSearch);
        }
        else
        {

        }
    }

    void PartOne(std::vector<std::vector<char>>& mat, int rows, int columns)
    {
        //Find the position of X.
        //For all it's 8 edges search for M.
        //If found, then alongs all it's edges search for A.
        //If found, then along all it's eges search for S.

        //While doing this check if every position is within the boundaries.
        int sum = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (mat[i][j] == 'X')
                {
                    int count = 0;
                    //Search the edges
                    if (TopLeft(mat, i - 1, j - 1, rows, columns, 'M'))
                        count++;
                    if (Top(mat, i - 1, j, rows, columns, 'M'))
                        count++;
                    if (TopRight(mat, i - 1, j + 1, rows, columns, 'M'))
                        count++;
                    if (Right(mat, i, j + 1, rows, columns, 'M'))
                        count++;
                    if (BottomRight(mat, i + 1, j + 1, rows, columns, 'M'))
                        count++;
                    if (Bottom(mat, i + 1, j, rows, columns, 'M'))
                        count++;
                    if (BottomLeft(mat, i + 1, j - 1, rows, columns, 'M'))
                        count++;
                    if (Left(mat, i, j - 1, rows, columns, 'M'))
                        count++;

                    sum += count;
                }
            }
        }

        std::cout << "Part One: " << sum << '\n';
    }


    bool BtRight(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return BtRight(mat, i + 1, j + 1, rows, columns, toSearch);
        }
        return false;
    }

    bool BtLeft(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return BtLeft(mat, i + 1, j - 1, rows, columns, toSearch);
        }
        return false;
    }

    bool TpRight(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return TpRight(mat, i - 1, j + 1, rows, columns, toSearch);
        }
        return false;
    }

    bool RtPlusTwo(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return BtLeft(mat, i + 1, j - 1, rows, columns, toSearch);
        }
        return false;
    }

    bool BtPlusTwo(std::vector<std::vector<char>>& mat, int i, int j, int rows, int columns, char c)
    {
        if (i < 0 || i >= rows || j < 0 || j >= columns)
            return 0;

        if (mat[i][j] == c)
        {
            char toSearch = ' ';
            if (c == 'A')
                toSearch = 'S';
            else if (mat[i][j] == 'S')
                return true;

            return TpRight(mat, i - 1, j + 1, rows, columns, toSearch);
        }
        return false;
    }

    void PartTwo(std::vector<std::vector<char>>& mat, int rows, int columns)
    {
        //M.S
        //.A.
        //M.S
        std::map<std::tuple<int, int>, std::tuple<int,int>> visited;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (mat[i][j] == 'M')
               {
                   if (visited.find(std::make_tuple(i, j)) != visited.end()) //Check if we have already visited these indices
                   {
                       if (BtRight(mat, i + 1, j + 1, rows, columns, 'A')) //We found 'MAS diagonally'
                       {
                           bool rtPlusTwo = RtPlusTwo(mat, i, j + 2, rows, columns, 'M');
                           bool btPlusTwo = BtPlusTwo(mat, i + 2, j, rows, columns, 'M');

                           if (rtPlusTwo)
                               visited[std::make_tuple(i, j)] = std::make_tuple(i, j + 2);
                           else if (btPlusTwo)
                               visited[std::make_tuple(i, j)] = std::make_tuple(i + 2, j);
                       }

                       if (BtLeft(mat, i + 1, j - 1, rows, columns, 'M'))
                       {

                       }
                   }
               }
               
            }
        }
    }
}