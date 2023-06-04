#pragma once
#include <vector>
#include <string>
#include <cassert>

std::vector<std::string> Split(const std::string& s, char seperator);

inline char intToHexChar(int i)
{
    assert(i >= 0 && i <= 15);
    return i >=0 && i <= 9 ? (char)(i + '0' - 0) :  (char)(i + 'a' - 10);
};

inline int hexCharToInt(char c)
{
    assert((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'));
    return (c >= '0' && c <= '9') ? (int)(c - ('0' - 0)) : (int)(c - ('a' - 10)); 
}