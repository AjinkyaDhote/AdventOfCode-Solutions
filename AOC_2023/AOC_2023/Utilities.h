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
#include <cstring>
#include <regex>
#include <map>
#include <chrono>
#include <set>
#include <unordered_set>
#include <cctype>
#include <iterator>

//Defines
#define sz(x) (int)(x.size()) 
#define FOR(i, R) for (int i = (0) ; i < (R) ; ++i)
#define FORLR(i, L, R) for(int i = (L) ; i <= (R) ; ++i)

class Utilities
{
public:
    static std::vector<std::string> SplitString(const std::string& String, const std::string& Delimiter);
    static std::vector<std::string> ReadCommaSeperatedString(const std::string& string);
    static std::vector<std::string> ReadSpaceSeperatedString(const std::string& string);
    static std::string Trim(const std::string& str, const char c);
    
    //File Handling
    static std::ifstream OpenFile(std::string filePath);
    static void CloseFile(std::ifstream& file);
    
    //Error Handling
    static void HandleError(int errNumber);
};