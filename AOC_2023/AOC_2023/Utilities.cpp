#include "Utilities.h"

std::vector<std::string> Utilities::SplitString(const std::string& str, const std::string& delimiter)
{
    std::vector<std::string> Tokens;

    size_t NextTokenStart = 0;

    while (NextTokenStart < str.size())
    {
        size_t DelimiterStart = str.find(delimiter, NextTokenStart);

        if (DelimiterStart == std::string::npos)
        {
            DelimiterStart = str.size();
        }

        std::string Token = str.substr(NextTokenStart, DelimiterStart - NextTokenStart);
        Tokens.push_back(Token);

        NextTokenStart = DelimiterStart + delimiter.size();
    }

    return Tokens;
}

std::vector<std::string> Utilities::ReadCommaSeperatedString(const std::string& string)
{
    std::vector<std::string> Tokens;
    std::stringstream ss(string);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        Tokens.push_back(token);
    }

    return Tokens;
}

std::vector<std::string> Utilities::ReadSpaceSeperatedString(const std::string& string)
{
    std::vector<std::string> Tokens;
    std::stringstream ss(string);
    std::string token;
    while (std::getline(ss, token, ' '))
    {
        if (!token.empty())
        {
            Tokens.push_back(token);
        }
    }

    return Tokens;
}

/// <summary>
/// Trim from front of the string (Left)
/// </summary>
std::string& Utilities::Ltrim(std::string& str, const char* c)
{
    str.erase(0, str.find_first_not_of(c));
    return str;
}

/// <summary>
/// Trim from back of the string (Right)
/// </summary>
std::string& Utilities::Rtrim(std::string& str, const char* c)
{
    str.erase(str.find_last_not_of(c));
    return str;
}

/// <summary>
/// Trim from both ends of the string (Right then Left)
/// </summary>
std::string& Utilities::trim(std::string& str, const char* c)
{
    return Ltrim(Rtrim(str, c), c);
}


std::ifstream Utilities::OpenFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (file.is_open())
    {
        return file;
    }
    perror(("error while opening file " + filePath).c_str());
    exit(EXIT_FAILURE);
}

void Utilities::CloseFile(std::ifstream& file)
{
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        perror("error while closing file.");
        exit(EXIT_FAILURE);
    }
}