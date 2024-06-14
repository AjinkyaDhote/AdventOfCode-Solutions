#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <string.h>
#include <regex>
#include <map>


class Utilities
{
public:
    static std::vector<std::string> SplitString(const std::string& String, const std::string& Delimiter);
    static std::vector<std::string> ReadCommaSeperatedString(const std::string& string);
    
    //File Handling
    static std::ifstream OpenFile(std::string filePath);
    static void CloseFile(std::ifstream& file);
    
    //Error Handling
    static void HandleError(int errNumber);
};